from io import BytesIO
import requests
from ecc.utils import (
    hash256,
    int_to_little_endian,
    little_endian_to_int,
    encode_varint,
    read_varint,
    SIGHASH_ALL,
)
from ecc.script import Script, p2pkh_script


class TxFetcher:
    cache = {}

    @classmethod
    def get_url(cls, testnet=False):
        """
        :param testnet: 테스트넷 여부
        :return: 풀 노드 url str값
        """
        if testnet:
            return "https://blockstream.info/testnet/api"
        else:
            return "https://blockstream.info/api"

    @classmethod
    def fetch(cls, tx_id, testnet=False, fresh=False):
        """
        찾고자 하는 트랜잭션 id롤 가지고 트랜잭션을 찾아 반환
            - 전체 트랜잭션을 반환
            - 해당 트랜잭션의 해시값(id)를 이용하여 검증을 하기 위해서
        :param tx_id: 찾고자 하는 트랜잭션 id
        :param testnet: 테스트넷 여부
        :param fresh: 캐시 이용 여부
        :return: 트랜잭션 id에 대응하는 트랜잭션 반환
        """
        if fresh or (tx_id not in cls.cache):
            url = "{}/tx/{}/hex".format(
                cls.get_url(testnet), tx_id
            )
            response = requests.get(url)
            try:
                raw = bytes.fromhex(response.text.strip())
            except ValueError:
                raise ValueError('unexpected response: {}'.format(response))

            if raw[4] == 0:
                raw = raw[:4] + raw[6:]
                tx = Tx.parse(BytesIO(raw), testnet=testnet)
                tx.locktime = little_endian_to_int(raw[-4:])
            else:
                tx = Tx.parse(BytesIO(raw), testnet=testnet)

            if tx.id() != tx_id:
                raise ValueError("Not the same id : {} vs {}".format(
                    tx.id(), tx_id
                ))

            cls.cache[tx_id] = tx

        cls.cache[tx_id].testnet = testnet
        return cls.cache[tx_id]


class Tx:
    """
    < 록타임 - locktime >
    - 트랜잭션 전파 후 실행을 지연시키는 방법 제공
        - 빈헌한 거래 상황(high-frequency trade)를 위해 고안
        - 록타임이 의미하는 시점에 도달하기 전에는 입력이 가리키는 비트코인을 소비 불가
        - 입력 트랜잭션(tx_inputs)의 시퀀스 값이 ffffffff이면 록타임 값이 무시
    - 4바이트의 리틀엔디언으로 직렬화
    - 보안 이슈
        - 록타임 도달시, 수신자가 해당 트랜잭션이 유효한지 확신 불가능
          ex) 시간이 많이 지나 부도 가능성이 있는 수표
        - 송신자가 톡타임 이전에 동일한 입력을 사용하는 트랜잭션을 만들고 블록체인에 포함시키면, 해당 트랜잭션이 무효화
        - BIT65에서 도입한 OP_CHECKLOCKTIMEVERIFY는 록타임까지 출력을 사용하지 못하게 하여 해당 문제 방지
    """

    command = b"tx"

    def __init__(self, version, tx_inputs, tx_outputs, locktime, testnet=False, segwit=False):
        """
        한 엔티티에서 다른 엔티티로의 가치 이동을 표현하는 클래스
        :param version: 트랜잭션의 버전. 어떤 부가 기능을 트랜잭션이 사용 가능한지 규정
        :param tx_inputs: 사용할 비트코인 정의 (TxIn 객체 배열)
        :param tx_outputs: 비트코인을 보내는 종착지 (TxOut 객체 배열)
        :param locktime: 해당 트랜잭션의 유효시점
        :param testnet: 테스트넷 여부 - 검증시 필요
        :param segwit: 세그윗 트랜잭션 여부
            - 세그윗 지원 여부에 따라 파싱 내용이 달라짐
        """
        self.version = version
        self.tx_inputs = tx_inputs
        self.tx_outputs = tx_outputs
        self.locktime = locktime
        self.testnet = testnet

        # 세그윗 관련 변수수
        self.segwit = segwit
        self._hash_prevouts = None
        self._hash_sequence = None
        self._hash_outputs = None

    def __repr__(self):
        tx_inputs = ""
        for tx_input in tx_inputs:
            tx_inputs += tx_input.__repr__() + "\n"

        tx_outputs = ""
        for tx_output in tx_outputs:
            tx_outputs += tx_output.__repr__() + "\n"

        return "tx: {}\nversion: {}\ntx_inputs: {}\ntx_outputs:{}\nlocktime: {}".format(
            self.id(), self.version, self.tx_inputs, self.tx_outputs, self.locktime
        )

    def id(self):
        """
        블록 탐색기(블록의 내용을 찾고 읽을 수 있는 도구) 등에서 트랜잭션을 탐색하는데 사용
        :return: 16진수 형식의 해시값
        """
        return self.hash().hex()

    def hash(self):
        """
        직렬화하여 hash256으로 해시값을 계산한 뒤, 리틀엔디언으로 변환
        - 트랜잭션 ID의 경우, 일반적인 직렬화 사용(?)
        :return: 트랜잭션 자체의 해시
        """
        return hash256(self.serialize_legacy())[::-1]

    def serialize(self):
        """
        세그윗 트랜잭션 여부에 따라 직렬화를 다르게 한다
        :return: 직렬화된 str
        """
        if self.segwit:
            return self.serialize_segwit()
        else:
            return self.serialize_legacy()

    def serialize_legacy(self):
        """
        세그윗이 아닌 일반 트랜잭션 직렬화
        :return: 직렬화된 str
        """
        # 버전 : 4바이트 리틀 엔디언
        result = int_to_little_endian(self.version, 4)
        # 이전 트랜잭션 정보 : 이전 트랜잭션 개수 및 이전 트랜잭션들의 정보
        result += encode_varint(len(self.tx_inputs))
        for tx_input in self.tx_inputs:
            result += tx_input.serialize()
        # 트랜잭션 출력 : 출력 개수 및 출력들의 정보
        result += encode_varint(len(self.tx_outputs))
        for tx_output in self.tx_outputs:
            result += tx_output.serialize()
        # 록타임 : 4바이트의 리틀엔디언
        result += int_to_little_endian(self.locktime, 4)

        return result

    def serialize_segwit(self):
        """
        세그윗 트랜잭션 직렬화
        - 이전 트랜잭션의 해제 스크립트는 증인 필드에 들어감
        - 증인 필드 관련 정보는 마지막에 직렬화
        :return: 직렬화된 str
        """
        # 버전 : 4바이트 리틀 엔디언
        result = int_to_little_endian(self.version, 4)

        # 마커 정보
        result += b"\x00\x01"

        # 이전 트랜잭션 정보 : 이전 트랜잭션 개수 및 이전 트랜잭션들의 정보
        result += encode_varint(len(self.tx_inputs))
        for tx_input in self.tx_inputs:
            result += tx_input.serialize()

        # 트랜잭션 출력 : 출력 개수 및 출력들의 정보
        result += encode_varint(len(self.tx_outputs))
        for tx_output in self.tx_outputs:
            result += tx_output.serialize()

        # 각 입력에 있는 증인 필드 : 가변 정수 형식
        for tx_in in self.tx_inputs:
            result += int_to_little_endian(len(tx_in.witness), 1)
            for item in tx_in.witness:
                if type(item) == int:
                    result += int_to_little_endian(item, 1)
                else:
                    result += encode_varint(len(item)) + item

        # 록타임 : 4바이트의 리틀엔디언
        result += int_to_little_endian(self.locktime, 4)

        return result

    @classmethod
    def parse(cls, stream, testnet=False):
        """
        직렬화된 정보를 파싱하는 클래스 메서드
        - 세그윗 트랜잭션 여부에 따라 파싱을 다르게 한다
        :param stream: 직렬화 정보에 대한 스트림
        :param testnet : 테스트넷 여부. 직렬화 정보에는 없는 정보
        :return: 역직렬화된 객체
        """
        # 세그윗 트랜잭션의 경우 5번째 바이트가 세그윗 마커
        stream.read(4)

        if stream.read(1) == b"\x00":
            parse_method = cls.parse_segwit
        else:
            parse_method = cls.parse_legacy

        # 스트림을 원상태로 복구하여 버전 정보를 가리키도록 한다
        stream.seek(-5, 1)

        return parse_method(stream, testnet)

    @classmethod
    def parse_legacy(cls, stream, testnet=False):
        """
        직렬화된 정보를 파싱하는 클래스 메서드 (세그윗 지원 이전)
        :param stream: 직렬화 정보에 대한 스트림
            - 직렬화 정보는 네트워크 통신이나 파일 입출력을 통해 받기 때문에 시간이 걸림
            - 받아야 하는 트랜잭션 크기(직렬화 크기)가 커지면 받을 때까지 파싱 불가능
            - 직렬화 정보의 스트림을 인수로 받아 파싱하면 효율적
              i.e 받은 데이터까지 파싱 진행 가능
        :param testnet : 테스트넷 여부. 직렬화 정보에는 없는 정보
        :return: 역직렬화된 객체
        """

        # 버전 : 4바이트 리틀엔디언
        version_info = stream.read(4)
        version = little_endian_to_int(version_info)

        # 사용할 비트코인 : 이전 트랜잭션 정보
        num_inputs = read_varint(stream)
        inputs = []
        for _ in range(num_inputs):
            inputs.append(TxIn.parse(stream))

        # 비트코인을 보내는 종착지 : 트랜잭션 출력 정보
        num_outputs = read_varint(stream)
        outputs = []
        for _ in range(num_outputs):
            outputs.append(TxOut.parse(stream))

        # 록타임 : 4바이트의 리틀엔디언
        locktime = little_endian_to_int(stream.read(4))

        return cls(version, inputs, outputs, locktime, testnet=testnet, segwit=False)

    @classmethod
    def parse_segwit(cls, stream, testnet=False):
        """
        세그윗 트랜잭션의 직렬화된 정보를 파싱하는 클래스 메서드
        - 세그윗 마커
        - 입력마다 있는 증인 필드
        :param stream: 직렬화 정보에 대한 스트림
        :param testnet: 테스트넷 여부. 직렬화 정보에는 없는 정보
        :return: 역직렬화된 객체
        """
        # 버전 : 4바이트 리틀엔디언
        version_info = stream.read(4)
        version = little_endian_to_int(version_info)

        # 세그윗 마커 정보 : 2바이트
        marker = stream.read(2)
        if marker != b"\x00\x01":
            raise RuntimeError("Not a segwit transaction : {}".format(marker))

        # 사용할 비트코인 : 이전 트랜잭션 정보
        num_inputs = read_varint(stream)
        inputs = []
        for _ in range(num_inputs):
            inputs.append(TxIn.parse(stream))

        # 비트코인을 보내는 종착지 : 트랜잭션 출력 정보
        num_outputs = read_varint(stream)
        outputs = []
        for _ in range(num_outputs):
            outputs.append(TxOut.parse(stream))

        # 입력마다 주어지는 증인(witness) 필드
        for tx_in in inputs:
            num_items = read_varint(stream)
            items = []
            for _ in range(num_items):
                item_len = read_varint(stream)
                if item_len == 0:
                    items.append(0)
                else:
                    items.append(stream.read(item_len))
            tx_in.witness = items

        # 록타임 : 4바이트의 리틀엔디언
        locktime = little_endian_to_int(stream.read(4))

        return cls(version, inputs, outputs, locktime, testnet=testnet, segwit=True)

    def fee(self):
        """
        트랜잭션 수수료
        - 모든 트랜잭션의 입력 합은 출력의 합보다 같거나 커야한다
            - 수수료가 0이면, 채굴자가 트랜잭션을 블록에 포함시킬 동기가 사라진다
            - 채굴자가 트랜잭션을 블록에 포함시키도록 하는 인센티브
        - (입력의 합) - (출력의 합)
            - 해당 수수료는 채굴자가 가져간다
            - 입력 필드인 TxIn에는 금액 필드가 없음
                => 이전 트랜잭션의 출력에서 찾아야 한다
            - UTXO 집합이나 제 3자가 제공하는 풀 노드로부터 이 정보를 얻어야한다
        :return: 해당 트랜잭션의 수수료
        """
        # 입력 트랜잭션의 합
        input_total_value = 0
        for tx_in in self.tx_inputs:
            input_total_value += tx_in.value(self.testnet)

        # 출력 트랜잭션의합
        output_total_value = 0
        for tx_out in self.tx_outputs:
            output_total_value += tx_out.amount

        # 수수료 계산
        return input_total_value - output_total_value

    def verify(self):
        """
        트랜잭션 검증
            : 트랜잭션을 수신한 후, 모든 노드가 해당 트랜잭션이 네트워크 규칙에 부합되도록 만들어 졌는지 확인하는 과정
        1. 이중 지불 방지
            - 트랜잭션 입력이 가리키는 비트코인이 존재하고 사용 가능한가?
        2. 새 비트코인 생성 방지
            - 해당 트랜잭션의 수수료가 0이상인가?
        3. 결합된 스크립트가 유효한지 확인
            - 입력의 해제 스크립트는 참조하는 트랜잭션 출력의 잠금 스크립트를 해제하는가?
        :return: 검증 결과 boolean
        """
        # 수수료가 음수인 경우 invalid
        if self.fee() < 0:
            return False

        # 각 입력이 올바른 해제 스크립트를 가지고 있는지 검증
        for i in range(len(self.tx_inputs)):
            if not self.verify_input(i):
                return False

        return True

    def sig_hash(self, input_index, reedem_script=None):
        """
        해제 스크립트에 서명을 포함시켜 트랜잭션을 변형
        step1 : 해제 스크립트 삭제
            - 서명 검증시 트랜잭션의 해제 스크립트 삭제
            - 서명 생성시 동일
            - 입력이 여러 개인 경우, 해당 입력의 해제 스크립트 삭제
        step2 : 이전 트랜잭션 출력의 잠금 스크립트를 입력의 스크립트에 삽입
            - p2pkh 스크립트
                - 입력의 해제 스크립트 삽입
                - 트랜잭션 입력에 대해 TxIn.script_pubkey를 사용하여 해제 스크립트 입수 가능
            - p2sh 스크립트
                - 리딤 스크립트 삽입
                - p2sh 스크립트를 사용하는 트랙잭션은 입력마다 리딤 스크립트를 가지고 있음
        step3 : 해시 유형 추가
            - 서명해시를 구하기 위한 메시지에 포함시킬 필드 결정
            - SIGHASH_ALL : 현재 입력과 다른 모든 입출력을 모두 포함
        step4 : 해시 계산
            - 최종 변경된 트랜잭션의 hash256 해시값 계산
            - 32바이트 빅엔디언 정수로 변환
        :param input_index: 현재 입력에 대한 인덱스
        :param reedem_script : h2sh 스크립트 사용시 해당 입력에 대한 리딤 스크립트
        :return: 변형된 트랜잭션의 서명해시 i.e 서명을 포함시킨 직렬화 정보
        """
        # 버전 : 4바이트 리틀 엔디언
        result = int_to_little_endian(self.version, 4)

        # 이전 트랜잭션 정보 : 이전 트랜잭션 개수 및 이전 트랜잭션들의 정보
        # 서명을 포함시키기 위해 serialize()와 다르게 직렬화
        result += encode_varint(len(self.tx_inputs))
        for idx, tx_in in enumerate(self.tx_inputs):
            # 현재 입력인 경우
            if idx == input_index:
                # 해제 스크립트를 대체할 스크립트 설정
                if reedem_script:
                    # h2sh 스크립트 사용시 해당 입력에 대한 리딤 스크립트로 스크립트 대체
                    script_sig = reedem_script
                else:
                    # 해당 트랜잭션 해시값에 대응되는 트랜잭션의 잠금 스크립트로 스크립트 대체
                    script_sig = tx_in.script_pubkey(self.testnet)
            # 다른 입력인 경우 : 해제 스크립트 없음
            else:
                script_sig = None

            tx_in_copy = TxIn(
                prev_tx=tx_in.prev_tx,
                prev_index=tx_in.prev_index,
                script_sig=script_sig,
                sequence=tx_in.sequence
            )
            result += tx_in_copy.serialize()

        # 트랜잭션 출력 : 출력 개수 및 출력들의 정보
        result += encode_varint(len(self.tx_outputs))
        for tx_output in self.tx_outputs:
            result += tx_output.serialize()

        # 록타임 : 4바이트의 리틀엔디언
        result += int_to_little_endian(self.locktime, 4)

        # 해시 유형 덧붙임 : SIGHASH_ALL 사용함
        result += int_to_little_endian(SIGHASH_ALL, 4)

        # 서명 해시 생성
        result256 = hash256(result)
        sig_message_hash = int.from_bytes(result256, "big")

        return sig_message_hash

    def verify_input(self, input_index):
        """
        현재 트랜잭션 입력에 대한 검증
        step 1 : 현재 입력에 대응하는 결합 스크립트 생성
            - 입력에 대응하는 이전 트랜잭션 출력의 잠금 스크립트
            - 입력의 해제 스크립트
                - p2sh의 경우 리딤 스크립트
                    - 호환성을 위해 p2wpkh/p2wsh 또한 리딤 스크립트에 포함
                - p2wpkh 스크립트의 경우, 증인필드(서명, 공개키)
        step 2 : 현재 입력에 대응하는 서명 생성
        step 3 : 결합 스크립트를 이용하여 서명 계산
        :param input_index: 현재 입력에 대한 인덱스
        :return: 검증 boolean
        """
        # 해당 트랜잭션 해시값에 대응되는 트랜잭션의 잠금 스크립트
        current_intput_tx = self.tx_inputs[input_index]
        current_pubkey = current_intput_tx.script_pubkey(testnet=self.testnet)

        # 스크립트 형식에 따라 리딤 스크립트 생성
        if current_pubkey.is_p2sh_script_pubkey():
            command = current_intput_tx.script_sig.commands[-1]
            redeem_script_raw = encode_varint(len(command)) + command
            redeem_script = Script.parse(BytesIO(redeem_script_raw))

            # 리딤 스크립트 : p2sh-p2wpkh 이거나 p2sh-p2wsh 이다
            # p2wpkh인 경우 :
            if redeem_script.is_p2wpkh_script_pubkey():
                message_hash = self.sig_hash_bip143(input_index, redeem_script)
                witness = current_intput_tx.witness
            # p2wsh인 경우
            elif redeem_script.is_p2wsh_script_pubkey():
                # 증인 스크립트 추출
                cmd = current_intput_tx.witness[-1]

                # 가변 길이의 증인 스크립트 파싱
                raw_witness = encode_varint(len(cmd)) + cmd
                witness_script = Script.parse(BytesIO(raw_witness))
                message_hash = self.sig_hash_bip143(input_index, witness_script=witness_script)
                witness = current_intput_tx.witness
            # p2sh인 경우
            else:
                message_hash = self.sig_hash(input_index, redeem_script)
                witness = None
        else:
            # 리딤 스크립트 : p2sh-p2wpkh 이거나 p2sh-p2wsh 이다
            # p2wpkh인 경우 :
            if current_pubkey.is_p2wpkh_script_pubkey():
                message_hash = self.sig_hash_bip143(input_index)
                witness = current_intput_tx.witness
            # p2wsh인 경우 :
            elif current_pubkey.is_p2wsh_script_pubkey():
                # 증인 스크립트 추출
                cmd = current_intput_tx.witness[-1]

                # 가변 길이의 증인 스크립트 파싱
                raw_witness = encode_varint(len(cmd)) + cmd
                witness_script = Script.parse(BytesIO(raw_witness))
                message_hash= self.sig_hash_bip143(input_index, witness_script=witness_script)
                witness = current_intput_tx.witness
            # p2sh인 경우
            else:
                message_hash = self.sig_hash(input_index)
                witness = None


        # 현재 트랜잭션 입력에 대한 결합 스크립트
        combined = current_intput_tx.script_sig + current_pubkey

        # 결합 스크립트를 통한 서명 검증
        return combined.evaluate(message_hash, witness)

    def sig_hash_bip143(self, input_index, redeem_script=None, witness_script=None):
        '''Returns the integer representation of the hash that needs to get
        signed for index input_index'''
        tx_in = self.tx_inputs[input_index]
        # per BIP143 spec
        s = int_to_little_endian(self.version, 4)
        s += self.hash_prevouts() + self.hash_sequence()
        s += tx_in.prev_tx[::-1] + int_to_little_endian(tx_in.prev_index, 4)
        if witness_script:
            script_code = witness_script.serialize()
        elif redeem_script:
            script_code = p2pkh_script(redeem_script.cmds[1]).serialize()
        else:
            script_code = p2pkh_script(tx_in.script_pubkey(self.testnet).cmds[1]).serialize()
        s += script_code
        s += int_to_little_endian(tx_in.value(), 8)
        s += int_to_little_endian(tx_in.sequence, 4)
        s += self.hash_outputs()
        s += int_to_little_endian(self.locktime, 4)
        s += int_to_little_endian(SIGHASH_ALL, 4)
        return int.from_bytes(hash256(s), 'big')

    def hash_prevouts(self):
        if self._hash_prevouts is None:
            all_prevouts = b''
            all_sequence = b''
            for tx_in in self.tx_inputs:
                all_prevouts += tx_in.prev_tx[::-1] + int_to_little_endian(tx_in.prev_index, 4)
                all_sequence += int_to_little_endian(tx_in.sequence, 4)
            self._hash_prevouts = hash256(all_prevouts)
            self._hash_sequence = hash256(all_sequence)
        return self._hash_prevouts

    def hash_sequence(self):
        if self._hash_sequence is None:
            self.hash_prevouts()  # this should calculate self._hash_prevouts
        return self._hash_sequence

    def hash_outputs(self):
        if self._hash_outputs is None:
            all_outputs = b''
            for tx_out in self.tx_outputs:
                all_outputs += tx_out.serialize()
            self._hash_outputs = hash256(all_outputs)
        return self._hash_outputs

    def sign_input(self, input_index, private_key):
        """
        현재 트랜잭션 입력에 해제 스크립트 생성
        :param input_index: 현재 입력에 대한 인덱스
        :param private_key: 해제 스크립트에 사용할 비밀키
        :return: 추가한 해제 스크립트 검증 결과 boolean
        """
        # 트랜잭션의 서명 해시
        message_hash = self.sig_hash(input_index)

        # 트랜잭션의 서명 해시에 대한 서명 der 직렬화
        der = private_key.sign(message_hash).der()

        # 스크립트에 들어가는 서명은 DER형식 서명과 1바이트의 해시 유형으로 구성
        sig = der + SIGHASH_ALL.to_bytes(1, "big")
        sec = private_key.public_key.sec()

        # 해당 트랜잭션의 입력의 해제 스크립트 추가
        script_sig = Script([sig, sec])
        self.tx_inputs[input_index].script_sig = script_sig

        # 추가한 해제 스크립트 검증
        return self.verify_input(input_index)

    def is_coinbase(self):
        """
        코인베이스 트랜잭션
        - 블록(일련의 트랜잭션 묶음)마다 들어가는 첫 번째 트랜잭션
        - 비트코인을 발행하는 유일한 트랜잭션
        - 트랜잭션의 출력은 p2pkh 잠금 스크립트
            - 채굴자가 지정한 주소에 블록 보상으로 주어지는 비트코인과 블록과 블록 내 모든 트랜잭션 수수료를 잠금
        - 코인베이스 트랜잭션 구조
            - 입력이 정확히 1개
            - 입력의 이전 트랜잭션 해시 값은 32바이트의 0
            - 입력이 이전 트랜잭션 출력번호는 ffffffff
        :return: 해당 트랜잭션이 코인베이스 트랜잭션인지 여부에 대한 boolean
        """
        # 입력의 개수는 1개
        if len(self.tx_inputs) != 1 :
            return False

        tx_input = self.tx_inputs[0]
        # 이전 트랜잭션의 해시와 출력번호
        return tx_input.prev_tx == b"\x00"*32 and \
            tx_input.prev_index == 0xffffffff

    def coinbase_height(self):
        """
        트랜잭션이 소속한 블록의 높이
        - 해제 스크립트의 첫 원소 규정
            - 채굴하고 있는 블록의 높이를 코인베이스 해제 스크립트의 첫 원소로 한다는 소프트포크 규정
            - 코인베이스 해제 스크립트를 통해 소속된 블록이 몇 번째 블록인지 확인 가능
            - 높이는 리틀엔디언 정수로 표현
        - 다른 블록에서 동일한 트랜잭션 ID를 갖는 문제 해결
            - 서로 다른 코인베이스 트랜잭션은 소속된 블록마다 높이가 다름
            - 해당 트랙잭션들의 직렬화 정보가 바이트 단위로 똑같을 수 없음
        - 소프트포크
        - 포크
            - 비트코인 네트워크를 구성하는 채굴 노드의 소프트웨어의 버전을 업데이트하는 것
                - 탈중앙화된 비트코인 네트워크는 동시 업데이트가 불가능
                - 각 채굴 노드는 점진적으로 버전업이 이루어짐
            - 소프트포크
                - 예전 버전 노드와 최신 버전 노드가 혼재되어 있어도 네트워크가 멈추지 않고 돌아가도록 갱신하는 것
       :return: 코인베이스 트랜잭션의 블록 높이
        """

        if not self.is_coinbase():
            raise ValueError("the transaction is not coinbase")

        tx_input = self.tx_inputs[0]
        script_sig = tx_input.script_sig
        return little_endian_to_int(script_sig.commands[0])


class TxIn:
    """
    비트코인 입력(트랜잭션 입력)
    - 트랜잭션 입력은 이전 트랜잭션의 출력 내용과 연관이 있음
    - 본인이 소유한 비트코인을 정확히 가리키기 위한 두가지 필요 사항
        1. 이전에 내가 수신한 비트코인을 가리키는 참조 정보
        2. 해당 비트코인이 나의 소유라는 증명
            : 타원곡선 서명 알고리즘(3장) 사용
    - 4가지 필드 존재
        - 이전 트랜잭션의 출력 정보
            1. 이전 트랜잭션의 해시값/ID
            2. 이전 트랜잭션의 출력 번호
        - 이전 트랜잭션의 출력을 사용하는 방법 정의
            3. 해제 스크립트
            4. 시퀀스

    1. 이전 트랜잭션의 해시값/ID
        - 이전 트랜잭션 해시값으로 hash256 사용
        - 해시 충돌이 거의 없어 이전 트랜잭션을 unique하게 특정 가능
        - 32바이트 리틀엔디언
    2. 이전 트랜잭션의 출력 번호
        - 각각의 트랜잭션은 하나 이상의 출력을 가진다
          i.e 사용하려는 이전 트랜잭션에서 출력이 여러 개일 가능성 존재
        - 몇번째 출력인지에 대한 정보 필요
        - 4바이트 리틀엔디언
    3. 해제 스크립트
        - 비트코인의 스마트 계약 언어인 Script를 구성하는 한 부분
        - 트랜잭션 출력의 소유자만이 할 수 있는 무엇인가를 나타냄
            : 금고를 열기 위한 열쇠
        - 가변 길이 필드로 시작
            - 해당 필드의 길이를 알아야 파싱 가능하기 때문
    4. 시퀀스
        - 빈번한 거래를 위해 록타임 필드와 함께 표기했던 필드
            - 록타임이 유요하는 동안 발생한 여러 거래를 하나의 트랜잭션으로 블록체인에 기록 가능
            - 최종 정산 결과만 기록하면 됨
            => 채굴자가 악용하기 쉬워 이런 방식으로 사용되지 않음
        - RBF(Replace-By-Fee)와 OP_CHECKSEQUENCEVERIFY로 사용
        - 4바이트 리틀엔디언

    """
    def __init__(self, prev_tx, prev_index, script_sig=None, sequence=0xffffffff):
        """
        :param prev_tx: 이전 트랜잭션의 해시값/ID
        :param prev_index: 이전 트랜잭션의 출력 번호
        :param script_sig: 해제 스크립트
        :param sequence: 시퀀스 필드
        """
        self.prev_tx = prev_tx
        self.prev_index = prev_index
        if script_sig is None:
            self.script_sig = Script()
        else:
            self.script_sig = script_sig
        self.sequence = sequence

    def __repr__(self):
        return "{}:{}".format(
            self.prev_tx.hex(),
            self.prev_index
        )

    @classmethod
    def parse(cls, stream):
        # 이전 트랜잭션 해시값 : 32바이트 리틀엔디언
        prev_tx = stream.read(32)[::-1]
        # 이전 트랜잭션 번호 : 4바이트 리틀엔디언
        prev_index = little_endian_to_int(stream.read(4))
        # 해제 스크립트
        script_sig = Script.parse(stream)
        # 시퀀스 필드 : 4바이트 리틀엔디언
        seqeunce = little_endian_to_int(stream.read(4))
        return cls(prev_tx, prev_index, script_sig, seqeunce)

    def serialize(self):
        # 이전 트랜잭션 해시값 : 32바이트 리틀엔디언
        result = self.prev_tx[::-1]
        # 이전 트랜잭션 번호 : 4바이트 리틀엔디언
        result += int_to_little_endian(self.prev_index, 4)
        # 해제 스크립트
        result += self.script_sig.serialize()
        # 시퀀스 필드 : 4바이트 리틀엔디언
        result += int_to_little_endian(self.sequence, 4)

        return result

    def fetch_tx(self, testnet=False):
        """
        :param testnet: 테스트넷 여부
        :return: 이전 트랜잭션 해시값(id)에 대응되는 트랜잭션(Tx 객체)
        """
        return TxFetcher.fetch(self.prev_tx.hex(), testnet=testnet)

    def value(self, testnet=False):
        """
        :param testnet: 테스트넷 여부
        :return: 이전 트랜잭션 해시값에 대응되는 트랜잭션의 비용
        """
        tx = self.fetch_tx(testnet=testnet)
        return tx.tx_outputs[self.prev_index].amount

    def script_pubkey(self, testnet=False):
        """
        :param testnet: 테스트넷 여부
        :return: 이전 트랜잭션 해시값에 대응되는 트랜잭션의 해제 스크립트
        """
        tx = self.fetch_tx(testnet=testnet)
        return tx.tx_outputs[self.prev_index].script_pubkey


class TxOut:
    """
    비트코인 출력(트랜잭션 출력)
    - 출력은 비트코인의 거래 후 종착지를 의미
    - 각 트랜잭션은 하나 이상의 출력을 가진다
      => 받는 사람이 여러 명인 경우, 하나의 트랜잭션으로 모든 사람에게 전송 가능
    - 2개의 필드
        1. 비트코인 금액
        2. 잠금 스크립트

    1. 비트코인 금액
        - 출력이 내포하는 비트코인의 양
        - 기본 단위는 사토시
            : 1억분의 1 비트코인
        - 8바이트 리틀엔디언으로 직렬화
    2. 잠금 스크립트
        - 비트코인의 스마트 계약 언어인 Script를 구성하는 한 부분
        - 잠긴 금고 역할
          => 금고 열쇠 소유자만 열수 있는 금고
        - 가변 길이 필드로 시작
    """
    def __init__(self, amount, script_pubkey):
        self.amount = amount
        self.script_pubkey = script_pubkey

    def __repr__(self):
        return "{}:{}".format(self.amount, self.script_pubkey)

    @classmethod
    def parse(cls, stream):
        # 금액 : 8바이트 리틀엔디언
        amount = little_endian_to_int(stream.read(8))
        # 해제 스크립트
        script_pubkey = Script.parse(stream)

        return cls(amount, script_pubkey)

    def serialize(self):
        # 금액 : 8바이트 리틀엔디언
        result = int_to_little_endian(self.amount, 8)
        # 해제 스크립트
        result += self.script_pubkey.serialize()

        return result

