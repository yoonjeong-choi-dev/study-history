import hashlib
from logging import getLogger
from ecc.secp256k1 import Signature, S256Point
from ecc.utils import hash256, hash160

LOGGER = getLogger(__name__)


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



"""
주요 연산자 구현
- 스크립트에서는 주어진 명령어를 한번에 하나씩 스택 기반으로 처리
- 명령어 종류
    - 데이터 : 스크립트 실행 명령어 집합 안에서 사용되는 데이터
    - 연산자 : 데이터에 대한 연산
"""
def op_checksig(stack, message_hash):
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

def op_mul(stack):
    if len(stack) < 2:
        return False

    elem1 = stack.pop()
    elem2 = stack.pop()

    try:
        ret = decode_num(elem1) * decode_num(elem2)
        stack.append(encode_num(ret))
        return True
    except (ValueError, SyntaxError) as e:
        return False

def op_checkmultisig(stack, message_hash):
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


"""
주어진 연산자
"""
def op_0(stack):
    stack.append(encode_num(0))
    return True


def op_1negate(stack):
    stack.append(encode_num(-1))
    return True


def op_1(stack):
    stack.append(encode_num(1))
    return True


def op_2(stack):
    stack.append(encode_num(2))
    return True


def op_3(stack):
    stack.append(encode_num(3))
    return True


def op_4(stack):
    stack.append(encode_num(4))
    return True


def op_5(stack):
    stack.append(encode_num(5))
    return True


def op_6(stack):
    stack.append(encode_num(6))
    return True


def op_7(stack):
    stack.append(encode_num(7))
    return True


def op_8(stack):
    stack.append(encode_num(8))
    return True


def op_9(stack):
    stack.append(encode_num(9))
    return True


def op_10(stack):
    stack.append(encode_num(10))
    return True


def op_11(stack):
    stack.append(encode_num(11))
    return True


def op_12(stack):
    stack.append(encode_num(12))
    return True


def op_13(stack):
    stack.append(encode_num(13))
    return True


def op_14(stack):
    stack.append(encode_num(14))
    return True


def op_15(stack):
    stack.append(encode_num(15))
    return True


def op_16(stack):
    stack.append(encode_num(16))
    return True


def op_nop(stack):
    return True


def op_if(stack, items):
    if len(stack) < 1:
        return False
    # go through and re-make the items array based on the top stack element
    true_items = []
    false_items = []
    current_array = true_items
    found = False
    num_endifs_needed = 1
    while len(items) > 0:
        item = items.pop(0)
        if item in (99, 100):
            # nested if, we have to go another endif
            num_endifs_needed += 1
            current_array.append(item)
        elif num_endifs_needed == 1 and item == 103:
            current_array = false_items
        elif item == 104:
            if num_endifs_needed == 1:
                found = True
                break
            else:
                num_endifs_needed -= 1
                current_array.append(item)
        else:
            current_array.append(item)
    if not found:
        return False
    element = stack.pop()
    if decode_num(element) == 0:
        items[:0] = false_items
    else:
        items[:0] = true_items
    return True


def op_notif(stack, items):
    if len(stack) < 1:
        return False
    # go through and re-make the items array based on the top stack element
    true_items = []
    false_items = []
    current_array = true_items
    found = False
    num_endifs_needed = 1
    while len(items) > 0:
        item = items.pop(0)
        if item in (99, 100):
            # nested if, we have to go another endif
            num_endifs_needed += 1
            current_array.append(item)
        elif num_endifs_needed == 1 and item == 103:
            current_array = false_items
        elif item == 104:
            if num_endifs_needed == 1:
                found = True
                break
            else:
                num_endifs_needed -= 1
                current_array.append(item)
        else:
            current_array.append(item)
    if not found:
        return False
    element = stack.pop()
    if decode_num(element) == 0:
        items[:0] = true_items
    else:
        items[:0] = false_items
    return True


def op_verify(stack):
    if len(stack) < 1:
        return False
    element = stack.pop()
    if decode_num(element) == 0:
        return False
    return True


def op_return(stack):
    return False


def op_toaltstack(stack, altstack):
    if len(stack) < 1:
        return False
    altstack.append(stack.pop())
    return True


def op_fromaltstack(stack, altstack):
    if len(altstack) < 1:
        return False
    stack.append(altstack.pop())
    return True


def op_2drop(stack):
    if len(stack) < 2:
        return False
    stack.pop()
    stack.pop()
    return True


def op_2dup(stack):
    if len(stack) < 2:
        return False
    stack.extend(stack[-2:])
    return True


def op_3dup(stack):
    if len(stack) < 3:
        return False
    stack.extend(stack[-3:])
    return True


def op_2over(stack):
    if len(stack) < 4:
        return False
    stack.extend(stack[-4:-2])
    return True


def op_2rot(stack):
    if len(stack) < 6:
        return False
    stack.extend(stack[-6:-4])
    return True


def op_2swap(stack):
    if len(stack) < 4:
        return False
    stack[-4:] = stack[-2:] + stack[-4:-2]
    return True


def op_ifdup(stack):
    if len(stack) < 1:
        return False
    if decode_num(stack[-1]) != 0:
        stack.append(stack[-1])
    return True


def op_depth(stack):
    stack.append(encode_num(len(stack)))
    return True


def op_drop(stack):
    if len(stack) < 1:
        return False
    stack.pop()
    return True


def op_dup(stack):
    if len(stack) < 1:
        return False
    stack.append(stack[-1])
    return True


def op_nip(stack):
    if len(stack) < 2:
        return False
    stack[-2:] = stack[-1:]
    return True


def op_over(stack):
    if len(stack) < 2:
        return False
    stack.append(stack[-2])
    return True


def op_pick(stack):
    if len(stack) < 1:
        return False
    n = decode_num(stack.pop())
    if len(stack) < n + 1:
        return False
    stack.append(stack[-n - 1])
    return True


def op_roll(stack):
    if len(stack) < 1:
        return False
    n = decode_num(stack.pop())
    if len(stack) < n + 1:
        return False
    if n == 0:
        return True
    stack.append(stack.pop(-n - 1))
    return True


def op_rot(stack):
    if len(stack) < 3:
        return False
    stack.append(stack.pop(-3))
    return True


def op_swap(stack):
    if len(stack) < 2:
        return False
    stack.append(stack.pop(-2))
    return True


def op_tuck(stack):
    if len(stack) < 2:
        return False
    stack.insert(-2, stack[-1])
    return True


def op_size(stack):
    if len(stack) < 1:
        return False
    stack.append(encode_num(len(stack[-1])))
    return True


def op_equal(stack):
    if len(stack) < 2:
        return False
    element1 = stack.pop()
    element2 = stack.pop()
    if element1 == element2:
        stack.append(encode_num(1))
    else:
        stack.append(encode_num(0))
    return True


def op_equalverify(stack):
    return op_equal(stack) and op_verify(stack)


def op_1add(stack):
    if len(stack) < 1:
        return False
    element = decode_num(stack.pop())
    stack.append(encode_num(element + 1))
    return True


def op_1sub(stack):
    if len(stack) < 1:
        return False
    element = decode_num(stack.pop())
    stack.append(encode_num(element - 1))
    return True


def op_negate(stack):
    if len(stack) < 1:
        return False
    element = decode_num(stack.pop())
    stack.append(encode_num(-element))
    return True


def op_abs(stack):
    if len(stack) < 1:
        return False
    element = decode_num(stack.pop())
    if element < 0:
        stack.append(encode_num(-element))
    else:
        stack.append(encode_num(element))
    return True


def op_not(stack):
    if len(stack) < 1:
        return False
    element = stack.pop()
    if decode_num(element) == 0:
        stack.append(encode_num(1))
    else:
        stack.append(encode_num(0))
    return True


def op_0notequal(stack):
    if len(stack) < 1:
        return False
    element = stack.pop()
    if decode_num(element) == 0:
        stack.append(encode_num(0))
    else:
        stack.append(encode_num(1))
    return True


def op_add(stack):
    if len(stack) < 2:
        return False
    element1 = decode_num(stack.pop())
    element2 = decode_num(stack.pop())
    stack.append(encode_num(element1 + element2))
    return True


def op_sub(stack):
    if len(stack) < 2:
        return False
    element1 = decode_num(stack.pop())
    element2 = decode_num(stack.pop())
    stack.append(encode_num(element2 - element1))
    return True


def op_booland(stack):
    if len(stack) < 2:
        return False
    element1 = decode_num(stack.pop())
    element2 = decode_num(stack.pop())
    if element1 and element2:
        stack.append(encode_num(1))
    else:
        stack.append(encode_num(0))
    return True


def op_boolor(stack):
    if len(stack) < 2:
        return False
    element1 = decode_num(stack.pop())
    element2 = decode_num(stack.pop())
    if element1 or element2:
        stack.append(encode_num(1))
    else:
        stack.append(encode_num(0))
    return True


def op_numequal(stack):
    if len(stack) < 2:
        return False
    element1 = decode_num(stack.pop())
    element2 = decode_num(stack.pop())
    if element1 == element2:
        stack.append(encode_num(1))
    else:
        stack.append(encode_num(0))
    return True


def op_numequalverify(stack):
    return op_numequal(stack) and op_verify(stack)


def op_numnotequal(stack):
    if len(stack) < 2:
        return False
    element1 = decode_num(stack.pop())
    element2 = decode_num(stack.pop())
    if element1 == element2:
        stack.append(encode_num(0))
    else:
        stack.append(encode_num(1))
    return True


def op_lessthan(stack):
    if len(stack) < 2:
        return False
    element1 = decode_num(stack.pop())
    element2 = decode_num(stack.pop())
    if element2 < element1:
        stack.append(encode_num(1))
    else:
        stack.append(encode_num(0))
    return True


def op_greaterthan(stack):
    if len(stack) < 2:
        return False
    element1 = decode_num(stack.pop())
    element2 = decode_num(stack.pop())
    if element2 > element1:
        stack.append(encode_num(1))
    else:
        stack.append(encode_num(0))
    return True


def op_lessthanorequal(stack):
    if len(stack) < 2:
        return False
    element1 = decode_num(stack.pop())
    element2 = decode_num(stack.pop())
    if element2 <= element1:
        stack.append(encode_num(1))
    else:
        stack.append(encode_num(0))
    return True


def op_greaterthanorequal(stack):
    if len(stack) < 2:
        return False
    element1 = decode_num(stack.pop())
    element2 = decode_num(stack.pop())
    if element2 >= element1:
        stack.append(encode_num(1))
    else:
        stack.append(encode_num(0))
    return True


def op_min(stack):
    if len(stack) < 2:
        return False
    element1 = decode_num(stack.pop())
    element2 = decode_num(stack.pop())
    if element1 < element2:
        stack.append(encode_num(element1))
    else:
        stack.append(encode_num(element2))
    return True


def op_max(stack):
    if len(stack) < 2:
        return False
    element1 = decode_num(stack.pop())
    element2 = decode_num(stack.pop())
    if element1 > element2:
        stack.append(encode_num(element1))
    else:
        stack.append(encode_num(element2))
    return True


def op_within(stack):
    if len(stack) < 3:
        return False
    maximum = decode_num(stack.pop())
    minimum = decode_num(stack.pop())
    element = decode_num(stack.pop())
    if element >= minimum and element < maximum:
        stack.append(encode_num(1))
    else:
        stack.append(encode_num(0))
    return True


def op_ripemd160(stack):
    if len(stack) < 1:
        return False
    element = stack.pop()
    stack.append(hashlib.new('ripemd160', element).digest())
    return True


def op_sha1(stack):
    if len(stack) < 1:
        return False
    element = stack.pop()
    stack.append(hashlib.sha1(element).digest())
    return True


def op_sha256(stack):
    if len(stack) < 1:
        return False
    element = stack.pop()
    stack.append(hashlib.sha256(element).digest())
    return True


def op_hash160(stack):
    # check that there's at least 1 element on the stack
    if len(stack) < 1:
        return False
    # pop off the top element from the stack
    element = stack.pop()
    # push a hash160 of the popped off element to the stack
    h160 = hash160(element)
    stack.append(h160)
    return True


def op_hash256(stack):
    if len(stack) < 1:
        return False
    element = stack.pop()
    stack.append(hash256(element))
    return True



def op_checksigverify(stack, z):
    return op_checksig(stack, z) and op_verify(stack)



def op_checkmultisigverify(stack, z):
    return op_checkmultisig(stack, z) and op_verify(stack)


def op_checklocktimeverify(stack, locktime, sequence):
    if sequence == 0xffffffff:
        return False
    if len(stack) < 1:
        return False
    element = decode_num(stack[-1])
    if element < 0:
        return False
    if element < 500000000 and locktime > 500000000:
        return False
    if locktime < element:
        return False
    return True


def op_checksequenceverify(stack, version, sequence):
    if sequence & (1 << 31) == (1 << 31):
        return False
    if len(stack) < 1:
        return False
    element = decode_num(stack[-1])
    if element < 0:
        return False
    if element & (1 << 31) == (1 << 31):
        if version < 2:
            return False
        elif sequence & (1 << 31) == (1 << 31):
            return False
        elif element & (1 << 22) != sequence & (1 << 22):
            return False
        elif element & 0xffff > sequence & 0xffff:
            return False
    return True



OP_CODE_FUNCTIONS = {
    0: op_0,
    79: op_1negate,
    81: op_1,
    82: op_2,
    83: op_3,
    84: op_4,
    85: op_5,
    86: op_6,
    87: op_7,
    88: op_8,
    89: op_9,
    90: op_10,
    91: op_11,
    92: op_12,
    93: op_13,
    94: op_14,
    95: op_15,
    96: op_16,
    97: op_nop,
    99: op_if,
    100: op_notif,
    105: op_verify,
    106: op_return,
    107: op_toaltstack,
    108: op_fromaltstack,
    109: op_2drop,
    110: op_2dup,
    111: op_3dup,
    112: op_2over,
    113: op_2rot,
    114: op_2swap,
    115: op_ifdup,
    116: op_depth,
    117: op_drop,
    118: op_dup,
    119: op_nip,
    120: op_over,
    121: op_pick,
    122: op_roll,
    123: op_rot,
    124: op_swap,
    125: op_tuck,
    130: op_size,
    135: op_equal,
    136: op_equalverify,
    139: op_1add,
    140: op_1sub,
    143: op_negate,
    144: op_abs,
    145: op_not,
    146: op_0notequal,
    147: op_add,
    148: op_sub,
    149: op_mul,
    154: op_booland,
    155: op_boolor,
    156: op_numequal,
    157: op_numequalverify,
    158: op_numnotequal,
    159: op_lessthan,
    160: op_greaterthan,
    161: op_lessthanorequal,
    162: op_greaterthanorequal,
    163: op_min,
    164: op_max,
    165: op_within,
    166: op_ripemd160,
    167: op_sha1,
    168: op_sha256,
    169: op_hash160,
    170: op_hash256,
    172: op_checksig,
    173: op_checksigverify,
    174: op_checkmultisig,
    175: op_checkmultisigverify,
    176: op_nop,
    177: op_checklocktimeverify,
    178: op_checksequenceverify,
    179: op_nop,
    180: op_nop,
    181: op_nop,
    182: op_nop,
    183: op_nop,
    184: op_nop,
    185: op_nop,
}

OP_CODE_NAMES = {
    0: 'OP_0',
    76: 'OP_PUSHDATA1',
    77: 'OP_PUSHDATA2',
    78: 'OP_PUSHDATA4',
    79: 'OP_1NEGATE',
    81: 'OP_1',
    82: 'OP_2',
    83: 'OP_3',
    84: 'OP_4',
    85: 'OP_5',
    86: 'OP_6',
    87: 'OP_7',
    88: 'OP_8',
    89: 'OP_9',
    90: 'OP_10',
    91: 'OP_11',
    92: 'OP_12',
    93: 'OP_13',
    94: 'OP_14',
    95: 'OP_15',
    96: 'OP_16',
    97: 'OP_NOP',
    99: 'OP_IF',
    100: 'OP_NOTIF',
    103: 'OP_ELSE',
    104: 'OP_ENDIF',
    105: 'OP_VERIFY',
    106: 'OP_RETURN',
    107: 'OP_TOALTSTACK',
    108: 'OP_FROMALTSTACK',
    109: 'OP_2DROP',
    110: 'OP_2DUP',
    111: 'OP_3DUP',
    112: 'OP_2OVER',
    113: 'OP_2ROT',
    114: 'OP_2SWAP',
    115: 'OP_IFDUP',
    116: 'OP_DEPTH',
    117: 'OP_DROP',
    118: 'OP_DUP',
    119: 'OP_NIP',
    120: 'OP_OVER',
    121: 'OP_PICK',
    122: 'OP_ROLL',
    123: 'OP_ROT',
    124: 'OP_SWAP',
    125: 'OP_TUCK',
    130: 'OP_SIZE',
    135: 'OP_EQUAL',
    136: 'OP_EQUALVERIFY',
    139: 'OP_1ADD',
    140: 'OP_1SUB',
    143: 'OP_NEGATE',
    144: 'OP_ABS',
    145: 'OP_NOT',
    146: 'OP_0NOTEQUAL',
    147: 'OP_ADD',
    148: 'OP_SUB',
    149: "OP_MUL",
    154: 'OP_BOOLAND',
    155: 'OP_BOOLOR',
    156: 'OP_NUMEQUAL',
    157: 'OP_NUMEQUALVERIFY',
    158: 'OP_NUMNOTEQUAL',
    159: 'OP_LESSTHAN',
    160: 'OP_GREATERTHAN',
    161: 'OP_LESSTHANOREQUAL',
    162: 'OP_GREATERTHANOREQUAL',
    163: 'OP_MIN',
    164: 'OP_MAX',
    165: 'OP_WITHIN',
    166: 'OP_RIPEMD160',
    167: 'OP_SHA1',
    168: 'OP_SHA256',
    169: 'OP_HASH160',
    170: 'OP_HASH256',
    171: 'OP_CODESEPARATOR',
    172: 'OP_CHECKSIG',
    173: 'OP_CHECKSIGVERIFY',
    174: 'OP_CHECKMULTISIG',
    175: 'OP_CHECKMULTISIGVERIFY',
    176: 'OP_NOP1',
    177: 'OP_CHECKLOCKTIMEVERIFY',
    178: 'OP_CHECKSEQUENCEVERIFY',
    179: 'OP_NOP4',
    180: 'OP_NOP5',
    181: 'OP_NOP6',
    182: 'OP_NOP7',
    183: 'OP_NOP8',
    184: 'OP_NOP9',
    185: 'OP_NOP10',
}
