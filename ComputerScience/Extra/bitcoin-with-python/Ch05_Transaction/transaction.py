from io import BytesIO
import requests
from ecc.utils import (
    hash256,
    int_to_little_endian,
    little_endian_to_int
)

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

    def fee(self, testnet=False):
        """
        :param testnet: 테스트넷 여부
        :return: 해당 트랜잭션의 수수료
        """
        # 입력 트랜잭션의 합
        input_total_value = 0
        for tx_in in self.tx_inputs:
            input_total_value += tx_in.value(testnet)

        # 출력 트랜잭션의합
        output_total_value = 0
        for tx_out in self.tx_outputs:
            output_total_value += tx_out.amount

        # 수수료 계산
        return input_total_value - output_total_value


def encode_varint(integer):
    """
    정수 필드를 가변 정수(variant integer)로 직렬화
    - 0 ~ 2^64-1 사이의 정숫값을 바이트로 표현하는 방법
    - 최대 8바이트로 표현
    - 접두부에 숫자 정보를 주어 가변 길이의 바이트로 표현
    :param integer: 0 ~ 2^64-1 사이의 정숫값
    :return: 가변 정수로 표현된 바이트형 값
    """
    # 0 ~ 252 사이 : 1바이트 표현
    if integer <0xfd:
        return bytes([integer])
    # 253 ~ 2^16-1 : 접두부 0xfd + 2바이트 리틀엔디언
    elif integer< 0x10000:
        return b"\xfd" + int_to_little_endian(integer, 2)
    # 2^16 ~ 2^32-1 : 접두부 0xfe + 4바이트 리틀엔디언
    elif integer< 0x10000:
        return b"\xfe" + int_to_little_endian(integer, 4)
    # 2^32 ~ 2^64-1 : 접두부 0xff + 2바이트 리틀엔디언
    elif integer< 0x10000:
        return b"\xff" + int_to_little_endian(integer, 8)
    else:
        raise ValueError("integer is too large : {}".format(integer))


def read_varint(stream):
    """
    직렬화된 가변 정수(variant integer)를 파싱
    :param stream: 직렬화한 바이트 정보를 담고 있는 스트림
    :return: 파싱한 정수
    """
    prefix = stream.read(1)[0]
    if prefix == 0xfd:
        return little_endian_to_int(stream.read(2))
    elif prefix == 0xfe:
        return little_endian_to_int(stream.read(4))
    elif prefix == 0xff:
        return little_endian_to_int(stream.read(8))
    else:
        return prefix

def exercise1():
    raw_tx = bytes.fromhex(
        '0100000001813f79011acb80925dfe69b3def355fe914bd1d96a3f5f71bf8303c6a989c7d1000000006b483045022100ed81ff192e75a3fd2304004dcadb746fa5e24c5031ccfcf21320b0277457c98f02207a986d955c6e0cb35d446a89d3f56100f4d7f67801c31967743a9c8e10615bed01210349fc4e631e3624a545de3f89f5d8684c7b8138bd94bdd531d2e213bf016b278afeffffff02a135ef01000000001976a914bc3b654dca7e56b04dca18f2566cdaf02e8d9ada88ac99c39800000000001976a9141c4bc762dd5423e332166702cb75f40df79fea1288ac19430600')
    stream = BytesIO(raw_tx)
    tx = Tx.parse(stream)
    print("Version {} : {}".format(tx.version, tx.version==1))

# 스크립트를 위해 임시 파일(6장 구현)
from ecc.script import Script

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




def example1():
    script_hex = "6b483045022100ed81ff192e75a3fd2304004dcadb746fa5e24c5031ccfcf21320b0277457c98f02207a986d955c6e0cb35d446a89d3f56100f4d7f67801c31967743a9c8e10615bed01210349fc4e631e3624a545de3f89f5d8684c7b8138bd94bdd531d2e213bf016b278a"
    stream = BytesIO(bytes.fromhex(script_hex))
    script_sig = Script.parse(stream)
    print(script_sig)

def exercise2():
    raw_tx = bytes.fromhex(
        '0100000001813f79011acb80925dfe69b3def355fe914bd1d96a3f5f71bf8303c6a989c7d1000000006b483045022100ed81ff192e75a3fd2304004dcadb746fa5e24c5031ccfcf21320b0277457c98f02207a986d955c6e0cb35d446a89d3f56100f4d7f67801c31967743a9c8e10615bed01210349fc4e631e3624a545de3f89f5d8684c7b8138bd94bdd531d2e213bf016b278afeffffff02a135ef01000000001976a914bc3b654dca7e56b04dca18f2566cdaf02e8d9ada88ac99c39800000000001976a9141c4bc762dd5423e332166702cb75f40df79fea1288ac19430600')
    stream = BytesIO(raw_tx)
    tx = Tx.parse(stream)
    size_of_tx_input = len(tx.tx_inputs)
    prev_tx = tx.tx_inputs[0].prev_tx
    prev_index = tx.tx_inputs[0].prev_index

    size_of_tx_input_ans = 1
    prev_tx_ans = bytes.fromhex('d1c789a9c60383bf715f3f6ad9d14b91fe55f3deb369fe5d9280cb1a01793f81')
    prev_index_ans = 0

    print("size of transaction input : {}".format(
        size_of_tx_input == size_of_tx_input_ans
    ))

    print("previous transaction ID : {}".format(
        prev_tx == prev_tx_ans
    ))

    print("previous transaction index : {}".format(
        prev_index == prev_index_ans
    ))


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





def exercise3():
    raw_tx = bytes.fromhex(
        '0100000001813f79011acb80925dfe69b3def355fe914bd1d96a3f5f71bf8303c6a989c7d1000000006b483045022100ed81ff192e75a3fd2304004dcadb746fa5e24c5031ccfcf21320b0277457c98f02207a986d955c6e0cb35d446a89d3f56100f4d7f67801c31967743a9c8e10615bed01210349fc4e631e3624a545de3f89f5d8684c7b8138bd94bdd531d2e213bf016b278afeffffff02a135ef01000000001976a914bc3b654dca7e56b04dca18f2566cdaf02e8d9ada88ac99c39800000000001976a9141c4bc762dd5423e332166702cb75f40df79fea1288ac19430600')
    stream = BytesIO(raw_tx)
    tx = Tx.parse(stream)
    tx_output_size = len(tx.tx_outputs)
    tx_output_amounts = (tx.tx_outputs[0].amount, tx.tx_outputs[1].amount)
    tx_output_script = (tx.tx_outputs[0].script_pubkey.serialize(), tx.tx_outputs[1].script_pubkey.serialize())

    tx_output_size_ans = 2
    tx_output_amounts_ans = (32454049, 10011545)
    tx_output_script_ans = (bytes.fromhex('1976a914bc3b654dca7e56b04dca18f2566cdaf02e8d9ada88ac'),
                            bytes.fromhex('1976a9141c4bc762dd5423e332166702cb75f40df79fea1288ac'))


    print("size of transaction output : {}".format(
        tx_output_size == tx_output_size_ans
    ))

    for i in range(tx_output_size):
        print("{}-th output".format(i+1))
        print("amount : {}".format(tx_output_amounts[i] == tx_output_amounts_ans[i]))
        print("script : {}".format(tx_output_script[i] == tx_output_script_ans[i]))
        print(tx_output_script[i])

def exercise4():
    raw_tx = bytes.fromhex(
        '0100000001813f79011acb80925dfe69b3def355fe914bd1d96a3f5f71bf8303c6a989c7d1000000006b483045022100ed81ff192e75a3fd2304004dcadb746fa5e24c5031ccfcf21320b0277457c98f02207a986d955c6e0cb35d446a89d3f56100f4d7f67801c31967743a9c8e10615bed01210349fc4e631e3624a545de3f89f5d8684c7b8138bd94bdd531d2e213bf016b278afeffffff02a135ef01000000001976a914bc3b654dca7e56b04dca18f2566cdaf02e8d9ada88ac99c39800000000001976a9141c4bc762dd5423e332166702cb75f40df79fea1288ac19430600')
    stream = BytesIO(raw_tx)
    tx = Tx.parse(stream)
    locktime = tx.locktime
    locktime_ans = 410393

    print("transaction locktime : {}".format(
        locktime == locktime_ans
    ))

def exercise5():
    raw_tx ="010000000456919960ac691763688d3d3bcea9ad6ecaf875df5339e148a1fc61c6ed7a069e010000006a47304402204585bcdef85e6b1c6af5c2669d4830ff86e42dd205c0e089bc2a821657e951c002201024a10366077f87d6bce1f7100ad8cfa8a064b39d4e8fe4ea13a7b71aa8180f012102f0da57e85eec2934a82a585ea337ce2f4998b50ae699dd79f5880e253dafafb7feffffffeb8f51f4038dc17e6313cf831d4f02281c2a468bde0fafd37f1bf882729e7fd3000000006a47304402207899531a52d59a6de200179928ca900254a36b8dff8bb75f5f5d71b1cdc26125022008b422690b8461cb52c3cc30330b23d574351872b7c361e9aae3649071c1a7160121035d5c93d9ac96881f19ba1f686f15f009ded7c62efe85a872e6a19b43c15a2937feffffff567bf40595119d1bb8a3037c356efd56170b64cbcc160fb028fa10704b45d775000000006a47304402204c7c7818424c7f7911da6cddc59655a70af1cb5eaf17c69dadbfc74ffa0b662f02207599e08bc8023693ad4e9527dc42c34210f7a7d1d1ddfc8492b654a11e7620a0012102158b46fbdff65d0172b7989aec8850aa0dae49abfb84c81ae6e5b251a58ace5cfeffffffd63a5e6c16e620f86f375925b21cabaf736c779f88fd04dcad51d26690f7f345010000006a47304402200633ea0d3314bea0d95b3cd8dadb2ef79ea8331ffe1e61f762c0f6daea0fabde022029f23b3e9c30f080446150b23852028751635dcee2be669c2a1686a4b5edf304012103ffd6f4a67e94aba353a00882e563ff2722eb4cff0ad6006e86ee20dfe7520d55feffffff0251430f00000000001976a914ab0c0b2e98b1ab6dbf67d4750b0a56244948a87988ac005a6202000000001976a9143c82d7df364eb6c75be8c80df2b3eda8db57397088ac46430600"
    raw_tx = bytes.fromhex(raw_tx)
    stream = BytesIO(raw_tx)

    tx = Tx.parse(stream)
    second_script_sig = tx.tx_inputs[1].script_sig
    first_script_pubkey = tx.tx_outputs[0].script_pubkey
    second_amount = tx.tx_outputs[1].amount

    problem = ["두번째 입력의 해제 스크립트", "첫 번째 출력의 잠금 스크립트", "두 번째 출력의 비트코인 금액"]
    my_answer = [second_script_sig, first_script_pubkey, second_amount]
    for i in range(3):
        print("{} - {}".format(problem[i], my_answer[i]))




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
            return "https://blockstream.info/testnet/api/"
        else:
            return "https://blockstream.info/api/"

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


def exercise6():
    raw_transactions = (
        bytes.fromhex('0100000001813f79011acb80925dfe69b3def355fe914bd1d96a3f5f71bf8303c6a989c7d1000000006b483045022100ed81ff192e75a3fd2304004dcadb746fa5e24c5031ccfcf21320b0277457c98f02207a986d955c6e0cb35d446a89d3f56100f4d7f67801c31967743a9c8e10615bed01210349fc4e631e3624a545de3f89f5d8684c7b8138bd94bdd531d2e213bf016b278afeffffff02a135ef01000000001976a914bc3b654dca7e56b04dca18f2566cdaf02e8d9ada88ac99c39800000000001976a9141c4bc762dd5423e332166702cb75f40df79fea1288ac19430600'),
        bytes.fromhex(
            '010000000456919960ac691763688d3d3bcea9ad6ecaf875df5339e148a1fc61c6ed7a069e010000006a47304402204585bcdef85e6b1c6af5c2669d4830ff86e42dd205c0e089bc2a821657e951c002201024a10366077f87d6bce1f7100ad8cfa8a064b39d4e8fe4ea13a7b71aa8180f012102f0da57e85eec2934a82a585ea337ce2f4998b50ae699dd79f5880e253dafafb7feffffffeb8f51f4038dc17e6313cf831d4f02281c2a468bde0fafd37f1bf882729e7fd3000000006a47304402207899531a52d59a6de200179928ca900254a36b8dff8bb75f5f5d71b1cdc26125022008b422690b8461cb52c3cc30330b23d574351872b7c361e9aae3649071c1a7160121035d5c93d9ac96881f19ba1f686f15f009ded7c62efe85a872e6a19b43c15a2937feffffff567bf40595119d1bb8a3037c356efd56170b64cbcc160fb028fa10704b45d775000000006a47304402204c7c7818424c7f7911da6cddc59655a70af1cb5eaf17c69dadbfc74ffa0b662f02207599e08bc8023693ad4e9527dc42c34210f7a7d1d1ddfc8492b654a11e7620a0012102158b46fbdff65d0172b7989aec8850aa0dae49abfb84c81ae6e5b251a58ace5cfeffffffd63a5e6c16e620f86f375925b21cabaf736c779f88fd04dcad51d26690f7f345010000006a47304402200633ea0d3314bea0d95b3cd8dadb2ef79ea8331ffe1e61f762c0f6daea0fabde022029f23b3e9c30f080446150b23852028751635dcee2be669c2a1686a4b5edf304012103ffd6f4a67e94aba353a00882e563ff2722eb4cff0ad6006e86ee20dfe7520d55feffffff0251430f00000000001976a914ab0c0b2e98b1ab6dbf67d4750b0a56244948a87988ac005a6202000000001976a9143c82d7df364eb6c75be8c80df2b3eda8db57397088ac46430600')
    )

    fees = []
    for raw_tx in raw_transactions:
        stream = BytesIO(raw_tx)
        tx = Tx.parse(stream)
        fees.append(tx.fee())

    answer = [40000, 140500]
    for i in range(2):
        print("{}-th problem : {}".format(
            i+1, fees[i] == answer[i]
        ))




if __name__ == "__main__":
    print("Chapter 5. Transaction")
    exercise1()
    example1()
    exercise2()
    exercise3()
    exercise4()
    exercise5()
    exercise6()






















