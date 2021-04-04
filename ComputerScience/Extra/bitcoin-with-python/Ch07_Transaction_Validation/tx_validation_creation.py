from io import BytesIO
import requests
from ecc.utils import (
    hash256,
    int_to_little_endian,
    little_endian_to_int,
    encode_varint,
    read_varint,
    BASE58_ALPHABET
)
from ecc.script import Script


SIGHASH_ALL = 1
SIGHASH_NONE = 2
SIGHASH_SINGLE = 3

class TxFetcher:
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
    """
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
        :param testnet: 테스트넷 여부
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

    def sig_hash(self, input_index):
        """
        해제 스크립트에 서명을 포함시켜 트랜잭션을 변형
        step1 : 해제 스크립트 삭제
            - 서명 검증시 트랜잭션의 해제 스크립트 삭제
            - 서명 생성시 동일
            - 입력이 여러 개인 경우, 해당 입력의 해제 스크립트 삭제
        step2 : 이전 트랜잭션 출력의 잠금 스크립트를 입력의 해제 스크립트에 삽입
            - 트랜잭션 입력에 대해 TxIn.script_pubkey를 사용하여 해제 스크립트 입수 가능
        step3 : 해시 유형 추가
            - 서명해시를 구하기 위한 메시지에 포함시킬 필드 결정
            - SIGHASH_ALL : 현재 입력과 다른 모든 입출력을 모두 포함
        step4 : 해시 계산
            - 최종 변경된 트랜잭션의 hash256 해시값 계산
            - 32바이트 빅엔디언 정수로 변환
        :param input_index: 현재 입력에 대한 인덱스
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
                # 해당 트랜잭션 해시값에 대응되는 트랜잭션의 잠금 스크립트로 스크립트 대체
                tx_in_copy = TxIn(
                    prev_tx=tx_in.prev_tx,
                    prev_index=tx_in.prev_index,
                    script_sig=tx_in.script_pubkey(self.testnet),
                    sequence=tx_in.sequence
                )
                result += tx_in_copy.serialize()
            # 다른 입력
            else:
                # 해제 스크립트는 포함시키지 않는다
                tx_in_copy = TxIn(
                    prev_tx=tx_in.prev_tx,
                    prev_index=tx_in.prev_index,
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

        # 현재 트랜잭션 입력에 대한 결합 스크립트
        combined = current_intput_tx.script_sig + current_pubkey

        # 현재 트랜잭션 입력에 대한 서명 생성
        message_hash = self.sig_hash(input_index)

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




def example1():
    print("Example 1 : 트랜잭션 수수료")
    raw_tx = (
        '0100000001813f79011acb80925dfe69b3def355fe914bd1d96a3f5f71bf8303c6a989c7d1000000006b483045022100ed81ff192e75a3fd2304004dcadb746fa5e24c5031ccfcf21320b0277457c98f02207a986d955c6e0cb35d446a89d3f56100f4d7f67801c31967743a9c8e10615bed01210349fc4e631e3624a545de3f89f5d8684c7b8138bd94bdd531d2e213bf016b278afeffffff02a135ef01000000001976a914bc3b654dca7e56b04dca18f2566cdaf02e8d9ada88ac99c39800000000001976a9141c4bc762dd5423e332166702cb75f40df79fea1288ac19430600')
    stream = BytesIO(bytes.fromhex(raw_tx))
    tx = Tx.parse(stream)
    print(tx.fee())

def example2():
    print("Example 2 : 서명 검증")
    from ecc.secp256k1 import S256Point, Signature
    sec = bytes.fromhex('0349fc4e631e3624a545de3f89f5d8684c7b8138bd94bdd531d2e213bf016b278a')
    der = bytes.fromhex(
        '3045022100ed81ff192e75a3fd2304004dcadb746fa5e24c5031ccfcf21320b0277457c98f02207a986d955c6e0cb35d446a89d3f56100f4d7f67801c31967743a9c8e10615bed')
    z = 0x27e0c5994dec7824e56dec6b2fcb342eb7cdb0d0957c2fce9882f715e85d81a6
    point = S256Point.parse(sec)
    signature = Signature.parse(der)
    print(point.verify(z, signature))

def exericse1():
    tx = TxFetcher.fetch('452c629d67e41baec3ac6f04fe744b4b9617f8f859c63b3002f8684e7a4fee03')
    sig_hash = tx.sig_hash(0)

    answer = int('27e0c5994dec7824e56dec6b2fcb342eb7cdb0d0957c2fce9882f715e85d81a6', 16)
    print("sig hash {} : {}".format(
        sig_hash, sig_hash == answer
    ))

def exercise2():
    tx1 = TxFetcher.fetch('452c629d67e41baec3ac6f04fe744b4b9617f8f859c63b3002f8684e7a4fee03')
    print("tx1 verify : {}".format(tx1.verify()))

    tx2 = TxFetcher.fetch('5418099cc755cb9dd3ebc6cf1a7888ad53a1a3beb5a025bce89eb1bf7f1650a2', testnet=True)
    print("tx2 verify : {}".format(tx2.verify()))



def decode_base58(encoded_str):
    """
    base58 기반 디코딩 함수
    - 비트코인 주소 생성시 Base58로 인코딩
    - 해당 주소로부터 20바이트 해시를 얻는 방법
    :param encoded_str: Base58로 인코딩된 비트코인 주소
    :return: 디코딩된 바이트의 중간 20바이트를 공개키의 hash160 해시값으로 반환
    """
    num = 0

    # 각 자리수 계산
    for c in encoded_str:
        num *=58
        num += BASE58_ALPHABET.index(c)

    # 25 바이트 빅엔디언으로 변환
    combined = num.to_bytes(25, byteorder="big")

    # 마지막 4바이트는 체크섬
    checksum = combined[-4:]

    # hash256 해시값의 체크섬과 비교
    if hash256(combined[:-4])[:4] != checksum:
        raise ValueError("Bad adress : {} {}".format(
            checksum, hash256(combined[:-4])[:4]
        ))

    # 첫 1바이트는 메인넷/테스트넷, 중간 20바이트는 공개키
    return combined[1:-4]

def p2pkh_script(h160):
    """
    encoder.decode_base58로 구한 해시값을 잠금 스크립트로 변환하는 함수
    - [OP_DUP, OP_HASH160, <hash>, OP_EQUALVERIFY, OP_CHECKSUM] 형태로 구성
    :param h160: 공개키의 hash160 해시값
    :return: 잠금 스크립트 객체
    """
    return Script([0x76, 0xa9, h160, 0x88, 0xac])


def example3():
    print("트랜잭션 생성 : 1개의 입력과 2개의 출력")

    # 트랜잭션 입력 1 : 테스트넷에서 트랜잭션 해시값과 출력 번호를 하나 찾아 설정
    prev_tx = bytes.fromhex('0d6fe5213c0b3291f208cba8bfb59b7476dffacc4e5cb66f6eb20a080843a299')
    prev_index = 13
    tx_in = TxIn(prev_tx, prev_index)

    # 비트코인을 보낼 주소 설정
    bitcoin_address = "mzx5YhAH9kNHtcN481u6WkjeHjYtVeKVh2"

    # 트랜잭션 출력 1
    change_amount = int(0.33*100000000)
    change_h160 = decode_base58(bitcoin_address)
    change_script = p2pkh_script(change_h160)
    change_output = TxOut(amount=change_amount, script_pubkey=change_script)

    # 트랜잭션 출력 2
    target_amount = int(0.1 * 100000000)
    target_h160 = decode_base58(bitcoin_address)
    target_script = p2pkh_script(target_h160)
    target_output = TxOut(amount=target_amount, script_pubkey=target_script)

    tx = Tx(1, [tx_in], [change_output, target_output], 0 , testnet=True)
    print(tx)

def example4():
    from ecc.secp256k1 import PrivateKey
    print("트랜잭션 해제 스크립트 생성")
    raw_tx = (
        '0100000001813f79011acb80925dfe69b3def355fe914bd1d96a3f5f71bf8303c6a989c7d1000000006b483045022100ed81ff192e75a3fd2304004dcadb746fa5e24c5031ccfcf21320b0277457c98f02207a986d955c6e0cb35d446a89d3f56100f4d7f67801c31967743a9c8e10615bed01210349fc4e631e3624a545de3f89f5d8684c7b8138bd94bdd531d2e213bf016b278afeffffff02a135ef01000000001976a914bc3b654dca7e56b04dca18f2566cdaf02e8d9ada88ac99c39800000000001976a9141c4bc762dd5423e332166702cb75f40df79fea1288ac19430600')
    stream = BytesIO(bytes.fromhex(raw_tx))
    tx = Tx.parse(stream)
    z = tx.sig_hash(0)

    # 비밀키 생성 및 트랜잭션의 서명 해시에 대한 서명 der 직렬화
    private_key = PrivateKey(secret=8675309)
    der = private_key.sign(z).der()

    # 스크립트에 들어가는 서명은 DER형식 서명과 1바이트의 해시 유형으로 구성
    sig = der + SIGHASH_ALL.to_bytes(1, "big")
    sec = private_key.public_key.sec()

    # 해당 트랜잭션의 입력의 해제 스크립트 추가
    script_sig = Script([sig, sec])
    tx.tx_inputs[0].script_sig = script_sig

    print(tx.serialize().hex())

def exercise3():
    from ecc.secp256k1 import PrivateKey
    private_key = PrivateKey(secret=8675309)
    stream = BytesIO(bytes.fromhex(
        '010000000199a24308080ab26e6fb65c4eccfadf76749bb5bfa8cb08f291320b3c21e56f0d0d00000000ffffffff02408af701000000001976a914d52ad7ca9b3d096a38e752c2018e6fbc40cdf26f88ac80969800000000001976a914507b27411ccf7f16f10297de6cef3f291623eddf88ac00000000'))
    tx = Tx.parse(stream, testnet=True)

    answer_tx = "010000000199a24308080ab26e6fb65c4eccfadf76749bb5bfa8cb08f291320b3c21e56f0d0d0000006b4830450221008ed46aa2cf12d6d81065bfabe903670165b538f65ee9a3385e6327d80c66d3b502203124f804410527497329ec4715e18558082d489b218677bd029e7fa306a72236012103935581e52c354cd2f484fe8ed83af7a3097005b2f9c60bff71d35bd795f54b67ffffffff02408af701000000001976a914d52ad7ca9b3d096a38e752c2018e6fbc40cdf26f88ac80969800000000001976a914507b27411ccf7f16f10297de6cef3f291623eddf88ac00000000"

    print("validate added script : {}".format(
        tx.sign_input(0, private_key)
    ))
    print("validate transaction : {}".format(
        tx.serialize().hex() == answer_tx
    ))

def my_address():
    from ecc.secp256k1 import PrivateKey
    my_message = b'YJ Choi secret'
    secret_key = little_endian_to_int(hash256(my_message))
    private_key = PrivateKey(secret_key)
    address = private_key.public_key.address(testnet=True)
    print(address)

if __name__ == "__main__":
    print("Ch 7. Transcation Validation and Creation")
    #example1()
    #example2()
    #exericse1()
    #exercise2()
    #example3()
    #example4()
    #exercise3()
    my_address()









