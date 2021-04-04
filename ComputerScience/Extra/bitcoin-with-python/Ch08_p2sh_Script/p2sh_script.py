from logging import getLogger
from io import BytesIO
from ecc.utils import (
    hash256,
    int_to_little_endian, little_endian_to_int,
    encode_varint, read_varint
)
from ecc.secp256k1 import (
    S256Point,
    Signature,
)
from ecc.op import (
    op_equal,
    op_hash160,
    op_verify,
    OP_CODE_FUNCTIONS,
    OP_CODE_NAMES
)
from ecc.op import (
    encode_num, decode_num
)

LOGGER = getLogger(__name__)

def op_checkmultisig_exercise(stack, message_hash):
    """
    m-of-n 다중 서명을 검증하는 명령어
    - m-of-n 다중 서명
        - n개의 공개키가 잠금 스크립트에 들어 있음
        - 해당 잠금 스크립트를 해제하기 위해서는 최소 m개의 비밀키를 활용해야 하는 서명
        - n개의 공개키 중에서 서로 다른 m개의 비밀키로 m개의 서명을 검증
    - 스택의 구성 (top에서부터 시작)
        - 공개키 정보
            - 공개키의 개수 n
            - n개의 공개키
        - 서명 정보
            - 비밀키의 개수 m
            - m개의 서명
        => (1+n) + (1+m) = m+n+2 개의 원소 필요
    - Off-by-One 버그
        - 해당 명령어는 m+n+3개의 원소를 가져옴
        - 추가로 가져오는 1개의 원소는 아무런 동작도 하지 않음
        - 현재 스택의 크기가 m+n+2개인 경우에 검증에 실패하는 버그
            => 원소가 모자르지 않도록 원소 1개를 미리 추가한 stack이 매개변수로 들어옴
    :param stack: 명령어 및 원소 스택
    :param message_hash: 메시지 해시
    :return: 실행 결과 boolean
    """

    if len(stack) < 1:
        return False

    # 공개키 개수
    n = decode_num(stack.pop())

    # 공개키가 모두 저장되어있는지 확인
    if len(stack) <= n:
        return False

    # 공개키 저장
    sec_pubkeys = []
    for _ in range(n):
        sec_pubkeys.append(stack.pop())

    # 비밀키 개수
    m = decode_num(stack.pop())

    # 비밀키가 모두 저장되어있는지 확인
    if len(stack) <= m:
        return  False

    # 비밀키에 해당하는 서명 저장
    der_signatures = []
    for _ in range(m):
        # 모든 der 서명은 SIGHASH_ALL로 서명된 것으로 간주
        der_signatures.append(stack.pop()[:-1])

    # Off-by-One 버그 => 미리 추가된 의미없는 원소를 삭제
    stack.pop()

    try:
        # 공개키 정보를 통해 공개키 객체(S256Point) 리스트 생성
        public_points = [S256Point.parse(sec_pubkey) for sec_pubkey in sec_pubkeys]

        # 비밀키에 대한 서명 정보를 통해 서명 객체(Signature) 리스트 생성
        signatures = [Signature.parse(der_signature) for der_signature in der_signatures]

        # 비밀키에 대한 서명 정보를 이용하여 공개키 검증
        for sig in signatures:
            # 검증을 해야하는 공개키가 없는 경우에는 검증 불가
            if len(public_points) == 0:
                return False

            # 검증을 해야하는 공개키들에 대해서 검증
            while public_points:
                public_point = public_points.pop(0)
                # 검증이 된다면 참
                if public_point.verify(message_hash, sig):
                    break

        # 검증이 되면 1을 추가한다
        stack.append(encode_num(1))    
    except (ValueError, SyntaxError):
        return False

    return True


def exercise1():
    z = 0xe71bfa115715d6fd33796948126f40a8cdd39f187e4afb03896795189fe1423c
    sig1 = bytes.fromhex(
        '3045022100dc92655fe37036f47756db8102e0d7d5e28b3beb83a8fef4f5dc0559bddfb94e02205a36d4e4e6c7fcd16658c50783e00c341609977aed3ad00937bf4ee942a8993701')
    sig2 = bytes.fromhex(
        '3045022100da6bee3c93766232079a01639d07fa869598749729ae323eab8eef53577d611b02207bef15429dcadce2121ea07f233115c6f09034c0be68db99980b9a6c5e75402201')

    sec1 = bytes.fromhex('022626e955ea6ea6d98850c994f9107b036b1334f18ca8830bfff1295d21cfdb70')
    sec2 = bytes.fromhex('03b287eaf122eea69030a0e9feed096bed8045c8b98bec453e1ffac7fbdbd4bb71')

    stack = [b'', sig1, sig2, b'\x02', sec1, sec2, b'\x02']

    is_valid_operation = op_checkmultisig_exercise(stack, z)
    result = stack[0]

    print("Is the operation valid : {}".format(is_valid_operation))
    print("reuslt of the operation : {}".format(decode_num(result)))


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

        p2sh 스크립트
        - 리딤 스크립트
            - 다중 서명 잠금 스크립트(공개키)에 해당
            - 다중 서명 스크립트의 경우 길이가 매우 길다
                => 다수의 공개키를 가지고 있어, 트랜잭션 출력의 잠금 스크립트 길이가 길어짐
        - 리딤 스크립트의 해시를 잠금 스크립트에 포함
            - [OP_HASH160, <hash>, OP_EQUAL] 형태
            - 리딤 스크립트 자체는 해제 스크립트에 포함
            - OP_HASH160(해제 스크립트의 리딤 스크립트) 와 <hash>가 같으면 유효하다고 판단
        - 리딤 스크립트에 대해서 유효하다고 판단한 경우
            - 리딤 스크립트의 명령어들(공개키포함)을 다시 명령어 집합(command)에 추가
            - 이후 명령 스택과 함께 명령어들을 실행
            - 명령어 집합이 [<리딤 스크립트>, OP_HASH160, <hash>, OP_EQUAL] 일 때가 예외 상황
                => 해당 집합 실행 후 유효하다고 판단하면, 리딤 스크립트의 명령어들을 명령어집합에 추가가
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

                # p2sh 예외 상황 : [OP_HASH160, <hash>, OP_EQUAL]
                if len(commands) == 3 and \
                    commands[0] == 0xa9 and \
                    type(commands[1]) == bytes and len(commands[1]) == 20 and \
                    commands[2] == 0x87:

                    # OP_HASH160는 필요 없음
                    commands.pop(0)

                    # 리딤스크립트의 해시값
                    redeem_h160 = commands.pop(0)

                    # OP_EQUAL도 필요없음
                    commands.pop(0)

                    # 스택에 있는 리딤스크립트(해제 스크립트에 있던)를 해시
                    if not op_hash160(stack):
                        return False

                    # 스택에 리딤스크립트의 해시값 추가
                    stack.append(redeem_h160)

                    # 잠금 스크립트에 있는 해시와 해시를 한 해제 스크립트 값 비교
                    if not op_equal(stack):
                        return False
                    if not op_verify(stack):
                        LOGGER.info("bad p2sh hash160 ")
                        print("bad p2sh hash160 ")
                        return False

                    # 스택에 넣었던 command가 리딤 스크립트
                    # 스크립트는 가변 길이 필드로 시작 => 스크립트 길이를 추가하여 파싱해야 한다
                    redeem_script = encode_varint(len(command)) + command
                    stream = BytesIO(redeem_script)

                    # 파싱한 명령어를 명령집합에 추가
                    commands.extend(Script.parse(stream).commands)

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

    # TODO : 연습문제 8.5
    def is_p2pkh_script_pubkey(self):
        """
        p2pkh 스크립트인지 확인
        - 명령집합이 [OP_DUP, OP_HASH160, <hash>, OP_EQUALVERIFY, OP_CHECKSUM] 형태로 구성
        - Script([0x76, 0xa9, h160, 0x88, 0xac])
        :return: p2pkh 스크립트 형식인지 boolean
        """
        return len(self.commands) == 5 and \
               self.commands[0] == 0x76 and \
               self.commands[1] == 0xa9 and \
               type(self.commands[2]) == bytes and len(self.commands[2]) == 20 and \
               self.commands[3] == 0x88 and self.commands[4] == 0xac

    def is_p2sh_script_pubkey(self):
        """
        p2sh 스크립트인지 확인
        - [OP_HASH160, <hash>, OP_EQUAL] 형태로 구성
        - Script([0xa9, h160, 0x87])
        :return: p2sh 스크립트 형식인지 boolean
        """
        return len(self.commands) == 3 and \
               self.commands[0] == 0xa9 and \
               type(self.commands[1]) == bytes and len(self.commands[1]) == 20 and \
               self.commands[2] == 0x87


def p2sh_script(h160):
    """
    encoder.decode_base58로 구한 해시값을 잠금 스크립트로 변환하는 함수
    - [OP_HASH160, <hash>, OP_EQUAL] 형태로 구성
    :param h160: 리딤 스크립트의 hash160 해시값
    :return: 잠금 스크립트 객체
    """
    return Script([0xa9, h160, 0x87])

from ecc.utils import encode_base58_checksum

def example1():
    h160 = bytes.fromhex('74d691da1574e6b3c192ecfb52cc8984ee7b6c56')
    print(encode_base58_checksum(b"\x05" + h160))



def h160_to_p2pkh_address(h160, testnet=False):
    """
    20바이트의 hash160 해시값을 p2pkh 주소로 변환
    :param h160: 공개키의 해시값
    :param testnet: 테스트넷 여부
    :return: p2pkh 주소
    """
    # 테스트넷의 경우
    if testnet:
        prefix = b"\x6f"
    # 메인넷의 경우
    else:
        prefix = b"\x00"

    return encode_base58_checksum(prefix + h160)

def h160_to_p2sh_address(h160, testnet=False):
    """
    20바이트의 hash160 해시값을 p2sh 주소로 변환
    :param h160: 리딤 스크립트의 해시값
    :param testnet: 테스트넷 여부
    :return: p2sh 주소
    """
    # 테스트넷의 경우
    if testnet:
        prefix = b"\xc4"
    # 메인넷의 경우
    else:
        prefix = b"\x05"

    return encode_base58_checksum(prefix + h160)


def exercise2():
    h160 = bytes.fromhex('74d691da1574e6b3c192ecfb52cc8984ee7b6c56')
    main_address = h160_to_p2pkh_address(h160)
    test_address = h160_to_p2pkh_address(h160, testnet=True)

    main_ans = '1BenRpVUFK65JFWcQSuHnJKzc4M8ZP8Eqa'
    test_ans = 'mrAjisaT4LXL5MzE81sfcDYKU3wqWSvf9q'

    print("main net address : {}".format(main_ans == main_address))
    print("test net address : {}".format(test_address == test_ans))

def exercise3():
    h160 = bytes.fromhex('74d691da1574e6b3c192ecfb52cc8984ee7b6c56')
    main_address = h160_to_p2sh_address(h160)
    test_address = h160_to_p2sh_address(h160, testnet=True)

    main_ans = '3CLoMMyuoDQTPRD3XYZtCvgvkadrAdvdXh'
    test_ans = '2N3u1R6uwQfuobCqbCgBkpsgBxvr1tZpe7B'

    print("main net address : {}".format(main_ans == main_address))
    print("test net address : {}".format(test_address == test_ans))

def example2():
    from ecc.secp256k1 import S256Point, Signature
    from ecc.utils import hash256

    modified_tx = bytes.fromhex(
        '0100000001868278ed6ddfb6c1ed3ad5f8181eb0c7a385aa0836f01d5e4789e6bd304d87221a000000475221022626e955ea6ea6d98850c994f9107b036b1334f18ca8830bfff1295d21cfdb702103b287eaf122eea69030a0e9feed096bed8045c8b98bec453e1ffac7fbdbd4bb7152aeffffffff04d3b11400000000001976a914904a49878c0adfc3aa05de7afad2cc15f483a56a88ac7f400900000000001976a914418327e3f3dda4cf5b9089325a4b95abdfa0334088ac722c0c00000000001976a914ba35042cfe9fc66fd35ac2224eebdafd1028ad2788acdc4ace020000000017a91474d691da1574e6b3c192ecfb52cc8984ee7b6c56870000000001000000')
    h256 = hash256(modified_tx)

    z = int.from_bytes(h256, 'big')

    # sec 공개키는 리딤 스크립트에서 구할 수 있음
    sec = bytes.fromhex('022626e955ea6ea6d98850c994f9107b036b1334f18ca8830bfff1295d21cfdb70')
    point = S256Point.parse(sec)

    # der 서명은 해제 스크립트에서 구할 수 있음
    der = bytes.fromhex(
        '3045022100dc92655fe37036f47756db8102e0d7d5e28b3beb83a8fef4f5dc0559bddfb94e02205a36d4e4e6c7fcd16658c50783e00c341609977aed3ad00937bf4ee942a89937')
    sig = Signature.parse(der)

    print(point.verify(z, sig))

def exercise4():
    from io import BytesIO
    from ecc.secp256k1 import S256Point, Signature
    from ecc.utils import encode_varint, hash256, int_to_little_endian
    from ecc.transaction import Tx, SIGHASH_ALL

    # 문제 : 주어진 p2sh 다중 서명 스크립트와 서명이 주어질 때, 해당 서명 검증
    hex_tx = '0100000001868278ed6ddfb6c1ed3ad5f8181eb0c7a385aa0836f01d5e4789e6bd304d87221a000000db00483045022100dc92655fe37036f47756db8102e0d7d5e28b3beb83a8fef4f5dc0559bddfb94e02205a36d4e4e6c7fcd16658c50783e00c341609977aed3ad00937bf4ee942a8993701483045022100da6bee3c93766232079a01639d07fa869598749729ae323eab8eef53577d611b02207bef15429dcadce2121ea07f233115c6f09034c0be68db99980b9a6c5e75402201475221022626e955ea6ea6d98850c994f9107b036b1334f18ca8830bfff1295d21cfdb702103b287eaf122eea69030a0e9feed096bed8045c8b98bec453e1ffac7fbdbd4bb7152aeffffffff04d3b11400000000001976a914904a49878c0adfc3aa05de7afad2cc15f483a56a88ac7f400900000000001976a914418327e3f3dda4cf5b9089325a4b95abdfa0334088ac722c0c00000000001976a914ba35042cfe9fc66fd35ac2224eebdafd1028ad2788acdc4ace020000000017a91474d691da1574e6b3c192ecfb52cc8984ee7b6c568700000000'
    hex_sec = '03b287eaf122eea69030a0e9feed096bed8045c8b98bec453e1ffac7fbdbd4bb71'
    hex_der = '3045022100da6bee3c93766232079a01639d07fa869598749729ae323eab8eef53577d611b02207bef15429dcadce2121ea07f233115c6f09034c0be68db99980b9a6c5e754022'
    hex_redeem_script = '475221022626e955ea6ea6d98850c994f9107b036b1334f18ca8830bfff1295d21cfdb702103b287eaf122eea69030a0e9feed096bed8045c8b98bec453e1ffac7fbdbd4bb7152ae'
    sec = bytes.fromhex(hex_sec)
    der = bytes.fromhex(hex_der)

    # 해답

    # sec 공개키와 der 서명을 통해 해당 객체 생성
    point = S256Point.parse(sec)
    signature = Signature.parse(der)

    redeem_script = Script.parse(BytesIO(bytes.fromhex(hex_redeem_script)))
    stream = BytesIO(bytes.fromhex(hex_tx))

    tx = Tx.parse(stream)


    # 두번째 서명을 만들기 위한 트랜잭션의 해시 계산
    sig = int_to_little_endian(tx.version, 4)

    # 이전 트랜잭션 정보 : 이전 트랜잭션 개수 및 이전 트랜잭션들의 정보
    sig += encode_varint(len(tx.tx_inputs))

    # 서명 : 트랜잭션 입력의 해제 스크립트를 리딤 스크립트로 대체
    cur_input = tx.tx_inputs[0]
    tx_in_copy = TxIn(
        prev_tx=cur_input.prev_tx,
        prev_index=cur_input.prev_index,
        script_sig=redeem_script,
        sequence=cur_input.sequence
    )
    sig += tx_in_copy.serialize()

    # 트랜잭션 출력 : 출력 개수 및 출력들의 정보
    sig += encode_varint(len(tx.tx_outputs))
    for tx_output in tx.tx_outputs:
        sig += tx_output.serialize()
    # 록타임 : 4바이트의 리틀엔디언
    sig += int_to_little_endian(tx.locktime, 4)

    # 해시 유형 덧붙임 : SIGHASH_ALL 사용함
    sig += int_to_little_endian(SIGHASH_ALL, 4)

    # 서명 해시 생성
    result256 = hash256(sig)
    sig_message_hash = int.from_bytes(result256, "big")

    print(point.verify(sig_message_hash, signature))




from ecc.transaction import TxIn, TxOut
from ecc.utils import SIGHASH_ALL
import requests
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



def exercise5():
    #from ecc.transaction import TxFetcher
    tx = TxFetcher.fetch('46df1a9484d0a81d03ce0ee543ab6e1a23ed06175c104a178268fad381216c2b')
    print("Verify the transaction with p2sh script : {}".format(tx.verify()))







if __name__ == "__main__":
    print("Chapter 8. p2sh Script")
    #exercise1()
    #example1()
    #exercise2()
    #exercise3()
    #example2()
    #exercise4()
    exercise5()