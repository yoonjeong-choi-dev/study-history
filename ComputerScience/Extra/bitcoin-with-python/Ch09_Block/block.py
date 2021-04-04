from io import BytesIO
import requests
from ecc.utils import (
    hash256,
    int_to_little_endian,
    little_endian_to_int,
    encode_varint,
    read_varint,
    SIGHASH_ALL,TWO_WEEKS
)
from ecc.script import Script
from ecc.transaction import TxIn, TxOut

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

    def __init__(self, version, tx_inputs, tx_outputs, locktime, testnet=False):
        """
        한 엔티티에서 다른 엔티티로의 가치 이동을 표현하는 클래스
        :param version: 트랜잭션의 버전. 어떤 부가 기능을 트랜잭션이 사용 가능한지 규정
        :param tx_inputs: 사용할 비트코인 정의 (TxIn 객체 배열)
        :param tx_outputs: 비트코인을 보내는 종착지 (TxOut 객체 배열)
        :param locktime: 해당 트랜잭션의 유효시점
        :param testnet: 테스트넷 여부 - 검증시 필요
        """
        self.version = version
        self.tx_inputs = tx_inputs
        self.tx_outputs = tx_outputs
        self.locktime = locktime
        self.testnet = testnet

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
        :return: 트랜잭션 자체의 해시
        """
        return hash256(self.serialize())[::-1]

    def serialize(self):
        """
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

    @classmethod
    def parse(cls, stream, testnet=False):
        """
        직렬화된 정보를 파싱하는 클래스 메서드
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

        return cls(version, inputs, outputs, locktime, testnet=testnet)

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
        step 2 : 현재 입력에 대응하는 서명 생성
        step 3 : 결합스크립트를 이용하여 서명 계산
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
        else:
            redeem_script = None

        # 현재 트랜잭션 입력에 대한 결합 스크립트
        combined = current_intput_tx.script_sig + current_pubkey

        # 현재 트랜잭션 입력에 대한 서명 생성
        message_hash = self.sig_hash(input_index, redeem_script)

        # 결합 스크립트를 통한 서명 검증
        return combined.evaluate(message_hash)

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
        if len(self.tx_inputs) != 1:
            return False

        tx_input = self.tx_inputs[0]
        # 이전 트랜잭션의 해시와 출력번호
        return tx_input.prev_tx == b"\x00" * 32 and \
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


def exercise1():
    raw_tx = bytes.fromhex(
        '01000000010000000000000000000000000000000000000000000000000000000000000000ffffffff5e03d71b07254d696e656420627920416e74506f6f6c20626a31312f4542312f4144362f43205914293101fabe6d6d678e2c8c34afc36896e7d9402824ed38e856676ee94bfdb0c6c4bcd8b2e5666a0400000000000000c7270000a5e00e00ffffffff01faf20b58000000001976a914338c84849423992471bffb1a54a8d9b1d69dc28a88ac00000000')
    stream = BytesIO(raw_tx)
    tx = Tx.parse(stream)
    print("Is coinbase : {}".format(tx.is_coinbase()))

def example1():
    print("Example : Miner-defined ScriptSig")
    stream = BytesIO(bytes.fromhex(
        '4d04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73'))
    script = Script.parse(stream)
    for cmd in script.commands:
        print(cmd)

def example2():
    print("Example : Height of Transaction in the block")
    stream = BytesIO(bytes.fromhex(
        '5e03d71b07254d696e656420627920416e74506f6f6c20626a31312f4542312f4144362f43205914293101fabe6d6d678e2c8c34afc36896e7d9402824ed38e856676ee94bfdb0c6c4bcd8b2e5666a0400000000000000c7270000a5e00e00'))
    script_sig = Script.parse(stream)
    print("Height : {}".format(little_endian_to_int(script_sig.commands[0])))

def exercise2():
    raw_tx = bytes.fromhex(
        '01000000010000000000000000000000000000000000000000000000000000000000000000ffffffff5e03d71b07254d696e656420627920416e74506f6f6c20626a31312f4542312f4144362f43205914293101fabe6d6d678e2c8c34afc36896e7d9402824ed38e856676ee94bfdb0c6c4bcd8b2e5666a0400000000000000c7270000a5e00e00ffffffff01faf20b58000000001976a914338c84849423992471bffb1a54a8d9b1d69dc28a88ac00000000')
    stream = BytesIO(raw_tx)
    tx = Tx.parse(stream)
    height = tx.coinbase_height()
    answer = 465879

    print("Height of transaction {} : {}".format(height, height==answer))


class Block:
    """
    블록
    - 트랜잭션의 묶음
        - 이중 지불 문제
            : 사용 권한이 있는 사람이 같은 비트코인을 여러 사람에게 보낼 때, 수신자들 중 1명만 사용가능한 문제
            => 트랜잭션 순서를 부여하여 첫번째만 유효하다고 판단하면 이중지물 문제 해결 가능
        - 순서를 부여하기 위해서는 모든 노드가 트랜잭션의 순서를 합의 해야함
            - 너무 짧은 시간에 합의를 하면, 노드 사이에 통신 비용이 많이 발생
            - 너무 긴 기간에 합의를 하면, 그 기간 동안 트랜잭션이 확정되지 않은 상태로 남음
            => 트랜잭션을 10분 간격으로 정산
        - 정산해야 하는 트랜잭션들의 묶음
    - 블록 헤더
        : 블록에 포함된 트랜잭션에 대한 메타데이터
        - 블록 버전(정수)
        - 이전 블록 해시값(바이트)
            - 중복된 해시값이 없으므로, 이전 블록 특정 가능
            - 블록체인 : 모든 블록은 체인처럼 연결
            - 모든 블록은 최초 블록까지 거슬러 올라간다
        - 머클루트(바이트)
            - 블록 내 순서에 따라 나열된 모든 트랜잭션을 32바이트 해시값으로 반환
        - 타임스탬프(정수)
            - 유닉스 형식으로 표현된 4바이트
                : 1970년 1월 1일 이후 시간을 초단위로 표현
            - 트랜잭션 록타임이 유닉스 형식인 경우, 해당 트랜잭션 활성화 시점을 알아내기 위한 비교 기준
            - 2016개 블록마다 비트값/목표값/난이도를 재계산 과정에서도 사용
            - 4바이트(32비트)를 사용하기 때문에 2016년 이후 사용 불가능
        - 비트값(바이트)
            - 블록에서 필요한 작업 증명 관련 필드
            - 목표값 생성에 필요
        - 논스값(바이트)
            - Nounce : Number used only ONCE
            - 작업 증명을 위해 채굴자가 변경하는 값
            - 논스값을 변경하면서, 블록 헤더의 해시 변경
              => 작업 증명에 사용
    """

    def __init__(self, version, prev_block, merkle_root, timestamp, bits, nounce):
        self.version = version
        self.prev_block = prev_block
        self.merkle_root = merkle_root
        self.timestamp = timestamp
        self.bits = bits
        self.nounce = nounce

    @classmethod
    def parse(cls, stream):
        """
        블록 헤더의 필드는 고정 길이
        - 정확히 80바이트
        - 버전과 타임스탬프만 정수이고, 나머지는 바이트형
        - 매우 작은 헤더의 크기는 단순 지급 검증(SPV, 11장) 기능에서 매우 중요
        """
        # 버전 : 4바이트 리틀엔디언
        version = little_endian_to_int(stream.read(4))

        # 이전 블록 해시값 : 32바이트 리틀엔디언
        prev_block = stream.read(32)[::-1]

        # 머클루트 : 32 바이트 리틀엔디언
        merkle_root = stream.read(32)[::-1]

        # 타임스탬프 : 4 바이트 리틀엔디언
        timestamp = little_endian_to_int(stream.read(4))

        # 비트값 : 4바이트
        bits = stream.read(4)

        # 논스값 : 4바이트
        nounce = stream.read(4)

        return cls(version, prev_block, merkle_root, timestamp, bits, nounce)

    def serialize(self):
        # 버전 : 4바이트 리틀엔디언
        result = int_to_little_endian(self.version, 4)

        # 이전 블록 해시값 : 32바이트 리틀엔디언
        result += self.prev_block[::-1]

        # 머클루트 : 32 바이트 리틀엔디언
        result += self.merkle_root[::-1]

        # 타임스탬프 : 4 바이트 리틀엔디언
        result += int_to_little_endian(self.timestamp, 4)

        # 비트값 : 4바이트
        result += self.bits

        # 논스값 : 4바이트
        result += self.nounce

        return result

    def hash(self):
        """
        직렬화하여 hash256으로 해시값을 계산한 뒤, 리틀엔디언으로 변환
        :return: 블록 ID
        """
        return hash256(self.serialize())[::-1]

    """
    블록 버전
    - 블록을 생성하는 비트코인 소프트웨어 기능의 집합
        - 초기에 채굴자에게 배포할 준비가 된 기능들을 말함
    - BIP0009 버전 
        - 한번에 서로 다른 기능의 준비 상황이 29개까지 표시되어 전파
        - 블록 헤더의 첫 3비트를 001로 설정
        - 이후 최대 29개의 새로운 기능 지원 여부를 나머지 29개의 비트에 표현
        - 2016개 블록 기간 동안 95%의 블록이 소프트포크 기능 준비 표시가 되면 해당 기능이 네트워크에서 승인되고 활성화
    """
    def bip9(self):
        """
        기능 전파에 사용되는 BIP0009 버전 여부 확인
        - 첫 3비트를 001로 설정
        :return: BIP9 기능 지원 여부
        """
        return self.version >> 29 == 0b001

    def bip91(self):
        """
        다섯번째 비트(비트 4)로 지원 여부 표현
        :return: BIP91 기능 지원 여부
        """
        return self.version >> 4 & 1 == 1

    def bip141(self):
        """
        세그윗(segwit) 지원 여부
        - 두번째 비트(비트 1)로 지원 여부 표현
        :return: BIP141 기능 지원 여부
        """
        return self.version >> 1 & 1 == 1

    def check_pow(self):
        """
        작업 증명
        - 작업 증명으로 탈중앙화 방식의 비트코인 채굴이 가능
          => 전체 네트워크 수준에서 비트코인 보안이 유지
        - 특정 조건을 만족하는 작은 값을 찾는 것
            - 특정 조건 : 목표값(target)
            - 작은 값 : 블록 헤더의 해시값
            - 블록의 해시값을 리틀엔디언 정수로 표현하여 비교
        - 블록 헤더의 해시 변경 방법
            - 채굴자가 논스값을 변경
            - 코인베이스 트랜잭션 변경
                => 머클루트가 변경되어 새로운 해시
            - 버전 필드 변경
        :return: 자격 증명 결과
        """
        block_hash = hash256(self.serialize())
        block_hash_int = little_endian_to_int(block_hash)
        return block_hash_int < self.target()

    def target(self):
        """
        :return: 목표값
        """
        return bits_to_target(self.bits)

    def difficulty(self):
        """
        난이도
        - 목표값의 수치를 통해 작업 증명을 찾는 것이 얼마나 어려운지에 대한 척도
        - 목표값이 작을 수록 해시값을 구하기 어려움
        - 난이도 = 0xffff * 256**(0x1d -3) / 목푯값
            - 0xffff : 65535
            - 0x1d : 29
        :return: 목표값의 난이도
        """
        difficulty = 0xffff * 256 ** (0x1d - 3) / self.target()
        return difficulty



def exercise3():
    block_raw = bytes.fromhex(
        '020000208ec39428b17323fa0ddec8e887b4a7c53b8c0a0a220cfd0000000000000000005b0750fce0a889502d40508d39576821155e9c9e3f5c3157f961db38fd8b25be1e77a759e93c0118a4ffd71d')
    stream = BytesIO(block_raw)
    block = Block.parse(stream)

    # answer
    version = 0x20000002
    prev_block = bytes.fromhex('000000000000000000fd0c220a0a8c3bc5a7b487e8c8de0dfa2373b12894c38e')
    merkle_root = bytes.fromhex('be258bfd38db61f957315c3f9e9c5e15216857398d50402d5089a8e0fc50075b')
    timestamp = 0x59a7771e
    bits = bytes.fromhex('e93c0118')
    nounce = bytes.fromhex('a4ffd71d')

    print("version : {}".format(block.version == version))
    print("prev_block : {}".format(block.prev_block == prev_block))
    print("merkle_root : {}".format(block.merkle_root == merkle_root))
    print("timestamp : {}".format(block.timestamp == timestamp))
    print("bits : {}".format(block.bits == bits))
    print("nounce : {}".format(block.nounce == nounce))

def exercise4():
    block_raw = bytes.fromhex(
        '020000208ec39428b17323fa0ddec8e887b4a7c53b8c0a0a220cfd0000000000000000005b0750fce0a889502d40508d39576821155e9c9e3f5c3157f961db38fd8b25be1e77a759e93c0118a4ffd71d')
    stream = BytesIO(block_raw)
    block = Block.parse(stream)
    print("block serialized : {}".format(block_raw == block.serialize()))

def exercise5():
    block_raw = bytes.fromhex(
        '020000208ec39428b17323fa0ddec8e887b4a7c53b8c0a0a220cfd0000000000000000005b0750fce0a889502d40508d39576821155e9c9e3f5c3157f961db38fd8b25be1e77a759e93c0118a4ffd71d')
    stream = BytesIO(block_raw)
    block = Block.parse(stream)

    block_hash = block.hash()
    answer = bytes.fromhex('0000000000000000007e9e4c586439b0cdbe13b1370bdd9435d76a644d047523')

    print("block hash : {}".format(block_hash == answer))

def example3():
    print("기능 준비 여부 확인")
    b = Block.parse(BytesIO(bytes.fromhex(
        '020000208ec39428b17323fa0ddec8e887b4a7c53b8c0a0a220cfd0000000000000000005b0750fce0a889502d40508d39576821155e9c9e3f5c3157f961db38fd8b25be1e77a759e93c0118a4ffd71d')))
    print('BIP9 Ready?: {}'.format(b.version >> 29 == 0b001))
    print('BIP91 Ready?: {}'.format(b.version >> 4 & 1 == 1))
    print('BIP141 Ready?: {}'.format(b.version >> 1 & 1 == 1))

def exercise6():
    block_raws = [
        bytes.fromhex(
            '020000208ec39428b17323fa0ddec8e887b4a7c53b8c0a0a220cfd0000000000000000005b0750fce0a889502d40508d39576821155e9c9e3f5c3157f961db38fd8b25be1e77a759e93c0118a4ffd71d'),
        bytes.fromhex(
            '0400000039fa821848781f027a2e6dfabbf6bda920d9ae61b63400030000000000000000ecae536a304042e3154be0e3e9a8220e5568c3433a9ab49ac4cbb74f8df8e8b0cc2acf569fb9061806652c27')
    ]

    answer = [True, False]

    for i, block_raw in enumerate(block_raws):
        stream = BytesIO(block_raw)
        block = Block.parse(stream)
        is_ready = block.bip9()
        print("BIP9 Ready ? - {} : {}".format(is_ready, is_ready==answer[i]))

def exercise7():
    block_raws = [
        bytes.fromhex(
            '1200002028856ec5bca29cf76980d368b0a163a0bb81fc192951270100000000000000003288f32a2831833c31a25401c52093eb545d28157e200a64b21b3ae8f21c507401877b5935470118144dbfd1'),
        bytes.fromhex(
            '020000208ec39428b17323fa0ddec8e887b4a7c53b8c0a0a220cfd0000000000000000005b0750fce0a889502d40508d39576821155e9c9e3f5c3157f961db38fd8b25be1e77a759e93c0118a4ffd71d')
    ]

    answer = [True, False]

    for i, block_raw in enumerate(block_raws):
        stream = BytesIO(block_raw)
        block = Block.parse(stream)
        is_ready = block.bip91()
        print("BIP91 Ready ? - {} : {}".format(is_ready, is_ready == answer[i]))

def exercise8():
    block_raws = [
        bytes.fromhex('020000208ec39428b17323fa0ddec8e887b4a7c53b8c0a0a220cfd0000000000000000005b0750fce0a889502d40508d39576821155e9c9e3f5c3157f961db38fd8b25be1e77a759e93c0118a4ffd71d'),
        bytes.fromhex('0000002066f09203c1cf5ef1531f24ed21b1915ae9abeb691f0d2e0100000000000000003de0976428ce56125351bae62c5b8b8c79d8297c702ea05d60feabb4ed188b59c36fa759e93c0118b74b2618')
    ]

    answer = [True, False]

    for i, block_raw in enumerate(block_raws):
        stream = BytesIO(block_raw)
        block = Block.parse(stream)
        is_ready = block.bip141()
        print("BIP141 Ready ? - {} : {}".format(is_ready, is_ready == answer[i]))

def example4():
    print("목표값 설정 : 블록헤더의 해시값이 목표값보다 작을 때 작업 증명 유효")

    # 목표값 계산
    bits = bytes.fromhex("e93c0118")
    exponent = bits[-1]
    coef = little_endian_to_int(bits[:-1])
    target = coef * 256**(exponent-3)
    print("exponent: {}, coef: {}".format(exponent, coef))
    print("target: ")
    print("{:x}".format(target).zfill(64))

    # 작업 증명 : 블록 헤더의 해시값을 리틀엔디언으로 표현
    block_hash = hash256(bytes.fromhex('020000208ec39428b17323fa0ddec8e887b4a7c53b8c0a0a220cfd0000000000000000005b0750fce0a889502d40508d39576821155e9c9e3f5c3157f961db38fd8b25be1e77a759e93c0118a4ffd71d'))
    block_hash_int = little_endian_to_int(block_hash)
    print("block_hash:")
    print("{:x}".format(block_hash_int).zfill(64))
    print("proof of work : {}".format(block_hash_int < target))


def bits_to_target(bits):
    """
    4바이트 비트를 작업 증명에 사용할 목표값으로 변환하는 함수
    - 지수 : 마지막 바이트
    - 계수 : 앞 세 바이트를 리틀엔디언으로 표현
    => target = 계수 * pow(256, 지수-3)
    :param bits: 4바이트 비트
    :return: 목표값
    """
    exponent = bits[-1]
    coef = little_endian_to_int(bits[:-1])
    target = coef * 256 ** (exponent - 3)
    return target


def exercise9():
    block_raw = bytes.fromhex(
        '020000208ec39428b17323fa0ddec8e887b4a7c53b8c0a0a220cfd0000000000000000005b0750fce0a889502d40508d39576821155e9c9e3f5c3157f961db38fd8b25be1e77a759e93c0118a4ffd71d')
    stream = BytesIO(block_raw)
    block = Block.parse(stream)
    target = block.target()
    answer = 0x13ce9000000000000000000000000000000000000000000

    print("Target : {}".format(target == answer))

def example5():
    print("Difficulty example")
    bits = bytes.fromhex("e93c0118")
    target = bits_to_target(bits)
    difficulty = 0xffff * 256**(0x1d-3) /target
    print(difficulty)

def exercise10():
    block_raw = bytes.fromhex(
        '020000208ec39428b17323fa0ddec8e887b4a7c53b8c0a0a220cfd0000000000000000005b0750fce0a889502d40508d39576821155e9c9e3f5c3157f961db38fd8b25be1e77a759e93c0118a4ffd71d')
    stream = BytesIO(block_raw)
    block = Block.parse(stream)
    difficulty = block.difficulty()

    answer = 888171856257
    print("Difficulty : {}".format(int(difficulty) == answer))

def exercise11():
    block_raws = [
        bytes.fromhex(
            '04000000fbedbbf0cfdaf278c094f187f2eb987c86a199da22bbb20400000000000000007b7697b29129648fa08b4bcd13c9d5e60abb973a1efac9c8d573c71c807c56c3d6213557faa80518c3737ec1'),
        bytes.fromhex(
            '04000000fbedbbf0cfdaf278c094f187f2eb987c86a199da22bbb20400000000000000007b7697b29129648fa08b4bcd13c9d5e60abb973a1efac9c8d573c71c807c56c3d6213557faa80518c3737ec0')
    ]

    answer = [True, False]

    for i, block_raw in enumerate(block_raws):
        stream = BytesIO(block_raw)
        block = Block.parse(stream)
        is_valid = block.check_pow()
        print("Proof of work ? - {} : {}".format(is_valid, is_valid == answer[i]))


def example6():
    last_block = Block.parse(BytesIO(bytes.fromhex(
        '00000020fdf740b0e49cf75bb3d5168fb3586f7613dcc5cd89675b0100000000000000002e37b144c0baced07eb7e7b64da916cd3121f2427005551aeb0ec6a6402ac7d7f0e4235954d801187f5da9f5')))
    first_block = Block.parse(BytesIO(bytes.fromhex(
        '000000201ecd89664fd205a37566e694269ed76e425803003628ab010000000000000000bfcade29d080d9aae8fd461254b041805ae442749f2a40100440fc0e3d5868e55019345954d80118a1721b2e')))
    time_differential = last_block.timestamp - first_block.timestamp

    if time_differential > TWO_WEEKS * 4:
        time_differential = TWO_WEEKS *4
    if time_differential < TWO_WEEKS // 4:
        time_differential = TWO_WEEKS //4

    new_target = last_block.target() * time_differential // TWO_WEEKS
    print("New Target")
    print("{:x}".format(new_target).zfill(64))


def target_to_bits(target):
    """
    목표값을 4바이트 비트로 변환하는 함수
    - 목표값 : target = 계수 * pow(256, 지수-3)
    :param target: 목표값
    :return: 4바이트 비트
    """
    raw_bytes = target.to_bytes(32, "big")
    raw_bytes = raw_bytes.lstrip(b"\x00")   # 앞에 있는 모든 0 제거

    # 음수 판단
    if raw_bytes[0] > 0x7f:
        # 목표값은 음수가 아니므로, 앞에서 제거한 1바이트의 0을 추가
        coef = b"\x00" + raw_bytes[:2]
        # 지수는 0이 아닌 수의 자릿수를 의미
        exponent = len(raw_bytes) + 1

    else:
        coef = raw_bytes[:3]
        exponent = len(raw_bytes)

    # 계수는 리틀엔디언으로 표현해줘야 함
    bits = coef[::-1] + bytes([exponent])
    return bits


def exercise12():
    block1_hex = '000000203471101bbda3fe307664b3283a9ef0e97d9a38a7eacd8800000000000000000010c8aba8479bbaa5e0848152fd3c2289ca50e1c3e58c9a4faaafbdf5803c5448ddb845597e8b0118e43a81d3'
    block2_hex = '02000020f1472d9db4b563c35f97c428ac903f23b7fc055d1cfc26000000000000000000b3f449fcbe1bc4cfbcb8283a0d2c037f961a3fdf2b8bedc144973735eea707e1264258597e8b0118e5f00474'

    block_raws = [bytes.fromhex(block1_hex), bytes.fromhex(block2_hex)]

    blocks = []
    for block_raw in block_raws:
        stream = BytesIO(block_raw)
        block = Block.parse(stream)
        blocks.append(block)

    first = blocks[1]
    last = blocks[0]

    time_diff = last.timestamp - first.timestamp

    if time_diff > TWO_WEEKS * 4:
        time_diff = TWO_WEEKS *4
    if time_diff < TWO_WEEKS // 4:
        time_diff = TWO_WEEKS //4

    new_target = last.target() * time_diff // TWO_WEEKS
    new_bits = target_to_bits(new_target)

    answer = "80df6217"

    print("New target bits - {} : {}".format(new_bits.hex(), new_bits.hex()==answer))


def calculate_new_bits(previous_bits, time_differential):
    # 마지막 블록 시간 - 첫번째 블록 시간 :  3.5일 이상 8주 이하로 clamp
    if time_differential > TWO_WEEKS * 4:
        time_differential = TWO_WEEKS *4
    if time_differential < TWO_WEEKS // 4:
        time_differential = TWO_WEEKS //4

    # 새 목표 값 = 이전 목표값 * 조정 기간 / 2주간의 초단위 시간
    previous_target = bits_to_target(previous_bits)
    new_target =  previous_target * time_differential // TWO_WEEKS
    new_bits = target_to_bits(new_target)
    return new_bits

def exercise13():
    prev_bits = bytes.fromhex('54d80118')
    time_differential = 302400
    new_bits = calculate_new_bits(prev_bits, time_differential)

    answer = bytes.fromhex('00157617')
    print("Next target bits : {}".format(new_bits == answer))


if __name__ == "__main__":
    print("Chapter 9. Block")
    #exercise1()
    #example1()
    #example2()
    #exercise2()
    #exercise3()
    #exercise4()
    #exercise5()
    #example3()
    #exercise6()
    #exercise7()
    #exercise8()
    #example4()
    #exercise9()
    #example5()
    #exercise10()
    #exercise11()
    #example6()
    #exercise12()
    exercise13()