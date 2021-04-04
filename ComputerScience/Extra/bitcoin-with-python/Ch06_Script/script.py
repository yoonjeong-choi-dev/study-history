from logging import getLogger
from ecc.utils import (
    encode_varint, read_varint,
    int_to_little_endian, little_endian_to_int
)
from ecc.op import OP_CODE_NAMES, OP_CODE_FUNCTIONS
from ecc.utils import hash160


LOGGER = getLogger(__name__)
"""
주요 연산자 구현
- 스크립트에서는 주어진 명령어를 한번에 하나씩 스택 기반으로 처리
- 명령어 종류
    - 데이터 : 스크립트 실행 명령어 집합 안에서 사용되는 데이터
    - 연산자 : 데이터에 대한 연산
- ecc.op 모듈을 그대로 사용함
"""
def op_hash160_exercise(stack):
    """
        스택 위 원소를 가져와 hash160을 적용하여 다시 스택 위에 올린다
        :param stack: 스택
        :return: 연산자 적용 여부
        """
    if len(stack) < 1:
        return False
    element = stack.pop()
    stack.append(hash160(element))
    return True

def exercise1():
    stack = [b'hello world']
    op_hash160_exercise(stack)
    result = stack[0]
    answer = "d7d5ee7824ff93f94c3055af9382c86c68b5ca92"
    print("op_hash160 test : {}".format(
        result.hex() == answer
    ))




class Script:
    """
    스크립트
    - 비트코인의 전송 메커니즘 : 비트코인을 잠그고 해제하는 방법
        - 잠근다 : 누군가에게 비트코인을 전송
        - 해제 : 내가 받은 비트코인을 소비
    - 비트코인의 스마트 계약 언어
        - 스마트 계약
            : 블록 체인상 코인의 선송을 프로그램으로 기술하는 것
        - 비트코인이 어떤 조건에서 소비되는지 기술하는 프로그래밍 언어
        - 스크립트를 통해 비트코인은 "계약"같은 것을 구현 가능
    - 스크립트에서는 주어진 명령어를 한번에 하나씩 스택 기반으로 처리
        - 명령어 종류
            - 데이터 : 스크립트 실행 명령어 집합 안에서 사용되는 데이터
        - 연산자 : 데이터에 대한 연산
    """
    def __init__(self, commands=None):
        """
        :param commands: 명령어 스택
        """
        if commands is None:
            self.commands = []
        else:
            self.commands = commands

    @classmethod
    def parse(cls, stream):
        """
        스크립트 파싱
        - 첫 1바이트를 읽어 n이라 한다
        - 0x01 ~ 0x4b(1~75) 사이의 값인 경우
            : 이어서 n바이트 길이를 읽어 해당 숫자를 한 원소로 간주
        - 0x4c 인 경우
            : OP_PUSHDATA1 에 해당
              => 바로 이후의 1 바이트 값이 그 다음 읽을 원소의 길이 정보를 표현
                 i.e OP_PUSHDATA1 <1바이트 리틀엔디언으로 표현한 원소 길이> <원소> 형태
        - 0x4d 인 경우
            : OP_PUSHDATA2 에 해당
              => 바로 이후의 2 바이트 값이 그 다음 읽을 원소의 길이 정보를 표현
                 i.e OP_PUSHDATA1 <2바이트 리틀엔디언으로 표현한 원소 길이> <원소> 형태
        -  78 이상인 경우
            : 해당 바이트(n)은 오피코드(연산자)
        :param stream: 직렬화한 스크립트의 스트림
        :return: 역질력화된 스크립트 객체
        """
        # 스크립트는 가변 길이 필드로 시작
        length = read_varint(stream)

        commands = []
        count = 0
        while count < length:
            current = stream.read(1)
            count += 1
            current_bytes = current[0]

            # 다음 current_bytes가 한 데이터 원소
            if 1 <= current_bytes <= 75:
                n = current_bytes
                commands.append(stream.read(n))
                count += n
            # 다음 한 바이트가 파싱할 데이터 원소의 길이
            elif current_bytes == 76:
                data_length = little_endian_to_int(stream.read(1))
                commands.append(stream.read(data_length))
                count += (data_length + 1)
            # 다음 두 바이트가 파싱할 데이터 원소의 길이
            elif current_bytes == 77:
                data_length = little_endian_to_int(stream.read(2))
                commands.append(stream.read(data_length))
                count += (data_length + 2)
            # 해당 바이트 자체가 오피코드
            else:
                op_code = current_bytes
                commands.append(op_code)

        # 스크립트 파싱이 정확하게 되었는지 확인
        if count != length:
            raise SyntaxError("Parsing srcipt failed")

        return cls(commands)

    def raw_serialize(self):
        result = b""
        for command in self.commands:
            # 명령어가 정수인 경우는 오피코드
            if type(command) == int:
                result += int_to_little_endian(command, 1)
            # 명령어가 바이트인 경우, 길이 정보를 추가
            else:
                length = len(command)
                # 길이가 75 이하이면, 1바이트로 표현
                if length <= 75:
                    result += int_to_little_endian(length, 1)
                # OP_PUSHDATA1 삽입 후, 1바이트로 표현
                elif 75 < length < 0x100:
                    result += int_to_little_endian(76, 1)
                    result += int_to_little_endian(length, 1)
                # OP_PUSHDATA2 삽입 후, 2바이트로 표현
                elif 0x100 <= length <= 520:
                    result += int_to_little_endian(77, 1)
                    result += int_to_little_endian(length, 2)
                else:
                    raise ValueError("too long an command")
                # 길이 정보 뒤에 실제 명령어 추가
                result += command
        return result

    def serialize(self):
        """
        :return: 길이 정보가 포함된 직렬화
        """
        # 명령어 집합에 대한 직렬화
        result = self.raw_serialize()
        # 길이 정보
        total = len(result)

        return encode_varint(total) + result

    def __add__(self, other):
        """
        스크립트 결합
        - 스크립트를 실행하기 위해서는 잠금 스크립트와 해제 스크립트가 필요
            - 잠금 스크립트(SriptPubkey)
                : 트랜잭션 출력(TxOut)의 스크립트 i.e 이전 트랜잭션의 출력의 스크립트
            - 해제 스크립트(ScriptSig)
                : 트랜잭션 입력(TxIn)의 스크립트 i.e 현재 트랜잭션의 스크립트
        - 두 스크립트는 서로 다른 트랜잭션에 존재
            - 잠금 스크립트(SriptPubkey)
                : 비트코인을 받았던 트랜잭션(이전 트랜잭션)에 존재
            - 해제 스크립트(ScriptSig)
                : 비트코인을 소비하는 트랜잭션(현재 트랜잭션)에 존재
        - 해제 스크립트는 잠금 스크팁립트로 잠긴 코인을 해제
            => 2개의 스크립트를 하나로 만드는 방법 필요
        :param other: 잠금 스크립트
        :return: 잠금 스크립트 위에 해제 스크립트를 올려놓은 결합 스크립트 객체
        """
        return Script(self.commands + other.commands)

    def evaluate(self, message_hash):
        """
        결합 스크립트(잠금+해제)의 명령어들을 실행
        - 실제에서는 해제 및 잠금 스크립트를 분리하여 실행
          (why?) 해제 스크립트가 잠금 스크립트 실행에 영향을 주지 않기 위해
        :param message_hash: 서명해시
        :return: 실행 결과 boolean
            - True 인 경우만 해당 결합 스크립트가 유효하다는 의미
              i.e 해제 스크립트로 잠금 스크립트를 해제 가능
        """
        # 스크립트 명령집합에서 명령어가 실행되면서 명령어가 하나씩 삭제
        # => commands 변수에 복사
        commands = self.commands[:]
        stack = []
        altstack = []

        while len(commands) > 0:
            command = commands.pop(0)

            # 연산자 명령인 경우 : 해당 명령 실행
            if type(command) == int:
                operation = OP_CODE_FUNCTIONS[command]

                # 흐름제어 명령어(99: op_if, 100: op_notif)
                if command in (99, 100):
                    # 명령을 수행하지 못하는 경우 로거에 남기고 거짓 반환
                    if not operation(stack, commands):
                        LOGGER.info("bad operation : {}".format(OP_CODE_NAMES[command]))
                        print("bad operation : {}".format(OP_CODE_NAMES[command]))
                        return False
                # 임시 스택(altstack)을 사용하는 명령어
                # 107: op_toaltstack, 108: op_fromaltstack
                elif command in (107, 108):
                    # 명령을 수행하지 못하는 경우 로거에 남기고 거짓 반환
                    if not operation(stack, altstack):
                        LOGGER.info("bad operation : {}".format(OP_CODE_NAMES[command]))
                        print("bad operation : {}".format(OP_CODE_NAMES[command]))
                        return False
                # 서명해시(message_hash)가 필요한 명령어
                # 172: op_checksig, 173: op_checksigverify
                # 174: op_checkmultisig, 175: op_checkmultisigverify,
                elif command in (172, 173, 174, 175):
                    # 명령을 수행하지 못하는 경우 로거에 남기고 거짓 반환
                    if not operation(stack, message_hash):
                        LOGGER.info("bad operation : {}".format(OP_CODE_NAMES[command]))
                        print("bad operation : {}".format(OP_CODE_NAMES[command]))
                        return False
                # 나머지 연산은 스택에 대한 연산들
                else:
                    if not operation(stack):
                        LOGGER.info("bad operation : {}".format(OP_CODE_NAMES[command]))
                        print("bad operation : {}".format(OP_CODE_NAMES[command]))
                        return False
            # 연산자가 데이터인 경우 : 스택에 저장
            else:
                stack.append(command)

        # 스택이 비어있는 경우, 스크립트 유효성 실패
        if len(stack) == 0:
            print("stack is empty")
            return  False
        # 스택의 최상위 원소가 비어있는 바이트인 경우에도 유효성 실패
        # op.py 모듈의 연산 함수의 검증 실패시 스택에 비어있는 바이트를 스택에 올림
        if stack.pop() == b"":
            print("stack has empty bytes")
            return False
        return True


def example1():
    z = 0x7c076ff316692a3d7eb3c3bb0f8b1488cf72e1afcd929e29307032997a838a3d
    sec = bytes.fromhex(
        '04887387e452b8eacc4acfde10d9aaf7f6d9a0f975aabb10d006e4da568744d06c61de6d95231cd89026e286df3b6ae4a894a3378e393e93a0f45b666329a0ae34')
    sig = bytes.fromhex(
        '3045022000eff69ef2b1bd93a66ed5219add4fb51e11a840f404876325a1e8ffe0529a2c022100c7207fee197d27c618aea621406f6bf5ef6fca38681d82b2f06fddbdce6feab601')

    script_pubkey = Script([sec, 0xac])
    script_sig = Script([sig])
    combined_script = script_sig + script_pubkey
    print(combined_script.evaluate(z))


"""
스택 원소(데이터)의 저장 형식
- int형 정수나 DER 서명이나 SEC 공개키같은 경우에는 bytes형 원소가 사용된다 
- 모든 원소는 bytes형으로 배열에 저장
    - 필요에 따라 해당 bytes형 원소를 정수로 해석
    - 산술 연산 오피코드에 대해서는 모든 bytes형 데이터를 리틀엔디언 정수로 해석
- encode_num    
    - 스택 위에 저장되는 정수는 bytes로 변환되어 저장
- decode_num
    - 스택에서 꺼내어 실제 정수값이 필요한 경우 정수형으로 변환되어 연산
"""

def encode_num(num):
    """
    :param num: int형 정수
    :return: 스크립트 스택에 저장하기 위해 변환된 bytes형
    """
    # 0인 경우 공바이트
    if num == 0:
        return b""

    abs_num = abs(num)
    negative = num < 0
    result = bytearray()

    # 절대값에 대해 바이트 단위(8비트)로 자리수 저장
    while abs_num:
        result.append(abs_num & 0xff)
        abs_num >>= 8

    # 비트 단위에서 음수 표현 (cf. 2의 보수)
    # 0x80 : 128
    if result[-1] & 0x80:
        if negative:
            result.append(0x80)
        else:
            result.append(0)
    elif negative:
        result[-1] |= 0x80
    return bytes(result)


def decode_num(element):
    """
    :param element: 스택에 저장된 bytes형 원소(데이터)
    :return: 연산자를 적용하기 위해 변환된 int형
    """
    # 공바이트는 0을 의미
    if element == b"":
        return 0

    # 원소는 리틀엔디언 => 빅 엔디언으로 변환
    big_endian = element[::-1]

    # 음수 판정
    if big_endian[0] & 0x80:
        negative = True
        result = big_endian[0] & 0x7f
    else:
        negative = False
        result = big_endian[0]

    # 각 자리수에 대해서 계산
    for d in big_endian[1:]:
        result <<=8
        result += d

    if negative:
        return -result
    else:
        return result



def example2():
    nums = [1,10,20,-15, 156, 255,123123,-123123]
    for num in nums:
        ret = encode_num(num)
        print("{} : {}".format(ret, decode_num(ret)))


from ecc.secp256k1 import S256Point, Signature
def op_checksig_exercise(stack, message_hash):
    """
    해제 스크립트가 올바른지 검증하는 부분
    - 올바른 경우, 스택에 1추가
    - 올바르지 않은 경우, 스택에 0추가
    :param stack: 명령어 및 원소 스택 
    :param message_hash: 메시지 해시
    :return: 실행 결과 boolean
    """
    # 필요한 원소는 2개
    # : 서명(der 직렬화)과 공개키(sec 직렬화)
    if len(stack) < 2:
        return False
    
    pubkey_sec = stack.pop()
    signature_der = stack.pop()[:-1]
    
    try:
        pubkey = S256Point.parse(pubkey_sec)
        signature = Signature.parse(signature_der)
    except (ValueError, SyntaxError) as e:
        return False
    
    # 서명 검증
    if pubkey.verify(z=message_hash, signature=signature):
        stack.append(encode_num(1))
    else:
        stack.append(encode_num(0))

    return True


def exercise2():
    z = 0x7c076ff316692a3d7eb3c3bb0f8b1488cf72e1afcd929e29307032997a838a3d
    sec = bytes.fromhex(
        '04887387e452b8eacc4acfde10d9aaf7f6d9a0f975aabb10d006e4da568744d06c61de6d95231cd89026e286df3b6ae4a894a3378e393e93a0f45b666329a0ae34')
    sig = bytes.fromhex(
        '3045022000eff69ef2b1bd93a66ed5219add4fb51e11a840f404876325a1e8ffe0529a2c022100c7207fee197d27c618aea621406f6bf5ef6fca38681d82b2f06fddbdce6feab601')
    stack = [sig, sec]

    op_success = op_checksig_exercise(stack, z)
    verified = decode_num(stack[0])

    print("Operation Success : {}".format(op_success))
    print("Validate Script : {}".format(verified))


# 149-OP_MUL을 op.py에 따로 구현해야함
def exercise3():
    # 767695935687 잠금 스크립트를 해제하는 해제 스크립트 작성
    script_pubkey = Script([0x76, 0x76, 0x95, 0x93, 0x56, 0x87])
    # x : 해제 스크립트 결과
    # => 잠금 스트립트 결과는 x^2 + x = 6
    # => x==2 i.e OP_2
    my_sig = Script([0x52])

    combined = my_sig + script_pubkey
    print(combined.evaluate(0))

if __name__ == "__main__":
    print("Chapter 6. Script")
    #exercise1()
    #example1()
    #example2()
    #exercise2()
    exercise3()
















