from logging import getLogger

from io import BytesIO
from ecc.utils import (
    int_to_little_endian, little_endian_to_int,
    encode_varint, read_varint,
    sha256
)

from ecc.op import (
    op_equal,
    op_hash160,
    op_verify,
    OP_CODE_FUNCTIONS,
    OP_CODE_NAMES
)

LOGGER = getLogger(__name__)


def p2pkh_script(h160):
    """
    encoder.decode_base58로 구한 해시값을 잠금 스크립트로 변환하는 함수
    - [OP_DUP, OP_HASH160, <hash>, OP_EQUALVERIFY, OP_CHECKSUM] 형태로 구성
    :param h160: 공개키의 hash160 해시값
    :return: 잠금 스크립트 객체
    """
    return Script([0x76, 0xa9, h160, 0x88, 0xac])

def p2sh_script(h160):
    """
    encoder.decode_base58로 구한 해시값을 잠금 스크립트로 변환하는 함수
    - [OP_HASH160, <hash>, OP_EQUAL] 형태로 구성
    :param h160: 리딤 스크립트의 hash160 해시값
    :return: 잠금 스크립트 객체
    """
    return Script([0xa9, h160, 0x87])

def p2wpkh_script(h160):
    """
    encoder.decode_base58로 구한 해시값을 잠금 스크립트로 변환하는 함수
    - [0x00, <hash>] 형태로 구성
    :param h160: 공개키의 hash160 해시값
    :return: 잠금 스크립트 객체
    """
    return Script([0x00, h160])


def p2wsh_script(h256):
    """
    sha256로 구한 해시값을 잠금 스크립트로 변환하는 함수
    - [0x00, <sha256>] 형태로 구성
    :param h256: 공개키의 sha256 해시값
    :return: 잠금 스크립트 객체
    """
    return Script([0x00, h256])


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

    def evaluate(self, message_hash, witness):
        """
        결합 스크립트(잠금+해제)의 명령어들을 실행
        - 실제에서는 해제 및 잠금 스크립트를 분리하여 실행
          (why?) 해제 스크립트가 잠금 스크립트 실행에 영향을 주지 않기 위해
        :param message_hash: 서명해시
        :param witness: 세그윗인 경우 증인 필드(해제 스크립트가 포함되어 있음)
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
                => 해당 집합 실행 후 유효하다고 판단하면, 리딤 스크립트의 명령어들을 명령어집합에 추가
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
                # p2wpkh 예외 상황 : [0x00, <hash>]
                if len(stack) == 2 and stack[0] == b'' and len(stack[1]) == 20:
                    # 0x00 은 필요없음
                    stack.pop(0)

                    # 증인 필드 해시값
                    h160 = stack.pop(0)

                    # 증인 필드(해제스크립트) 포함
                    commands.extend(witness)

                    # 증인 필드 해시값을 통해 생성한 p2p2kh 스크립트의 명령어 추가
                    # 증인 필드와 증인필드 해시값을 비교하기 위한 작업
                    commands.extend(p2pkh_script(h160).commands)
                # p2wsh 예외 상황 : [0x00, <sha256>] - p2sh와 유사
                if len(stack) == 2 and stack[0] == b'' and len(stack[1]) == 32:
                    # 0x00 은 필요없음
                    stack.pop(0)

                    # 증인 필드 해시값
                    s256 = stack.pop()
                    commands.extend(witness[:-1])

                    # 증인 스크립트 : 증인 필드의 가장 마지막 항목
                    witness_script = witness[-1]

                    # 증인 스크립트의 해시와 잠금 스크립트의 해시값 검증
                    if s256 != sha256(witness_script):
                        print('bad sha256 {} vs {}'.format
                            (s256.hex(), sha256(witness_script).hex()))
                        return False

                    # 증인 스크립트 팡싱
                    # 스크립트는 가변 길이 필드로 시작 => 스크립트 길이를 추가하여 파싱해야 한다
                    stream = BytesIO(encode_varint(len(witness_script))
                        + witness_script)
                    witness_script_cmds = Script.parse(stream).commands
                    commands.extend(witness_script_cmds)

        # 스택이 비어있는 경우, 스크립트 유효성 실패
        if len(stack) == 0:
            print("stack is empty")
            return False
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

    def is_p2wpkh_script_pubkey(self):
        """
        p2wpkh 스크립트인지 확인
        - [0x00, <hash>] 형태로 구성
        - Script([0x00, h160]) 형태
        :return: p2wpkh 스크립트 형식인지 boolean
        """
        return len(self.commands) == 2 and self.commands[0] == 0x00 \
            and type(self.commands[1]) == bytes and len(self.commands[1]) == 20

    def is_p2wsh_script_pubkey(self):
        """
        p2wsh 스크립트인지 확인
        - [0x00, <sha256>] 형태로 구성
        - Script([0x00, <sha256>]) 형태
        :return: p2wsh 스크립트 형식인지 boolean
        """
        return len(self.commands) == 2 and self.commands[0] == 0x00 \
            and type(self.commands[1]) == bytes and len(self.commands[1]) == 32
