import hashlib
from hashlib import sha256

SIGHASH_ALL = 1
SIGHASH_NONE = 2
SIGHASH_SINGLE = 3
BASE58_ALPHABET = '123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz'
TWO_WEEKS = 60 * 60 * 24 * 14

def hash256(message):
    """
    메시지의 해시값을 계산하는 함수
        - 비트코인에서는 sha256 함수를 두 번 적용
        - 해시 충돌과 같은 공격을 최소화하기 위해 두번 적용
    :param message: 메시지
    :return: 해시값
    """
    return sha256(sha256(message).digest()).digest()

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



def encode_base58(bytes_string):
    """
    base58 기반 인코딩
    :param bytes_string: 16진수 str
    :return: Base58로 인코딩된 str
    """
    count = 0
    # 맨 앞에 연속되는 0인 바이트들을 계산한다
    for c in bytes_string:
        if c == 0:
            count +=1
        else:
            break
    # 앞의 0인 바이드틀을 1로 붙여 구분
    # : pay-to-pubkey-has(p2pkh)에서 필요(6장 스크립트트
    prefix = "1" * count

    num = int.from_bytes(bytes_string, "big")
    result = ""
    # 각 자리에 사용되는 Base58 숫자 결정
    while num >0:
        num, mod = divmod(num, 58)
        result = BASE58_ALPHABET[mod] + result

    return prefix + result

def encode_base58_checksum(bytes_string):
    """
    특정 바이트와 체크섬(해당 바이트의 hash256 값에서 4비트를 취하여 연결한뒤 Base58로 인코딩
    - 시작 바이트(주소 종류) 및 SEC 형식 주소를 합친 결과와 해당 결과의 체크섬을 합쳐서 Base58로 인코딩
    :param bytes_string: 시작 바이트(주소 종류) 및 SEC 형식 주소를 합친 결과 str
    :return: Base58로 인코딩된 str(체크섬이 포함)
    """
    return encode_base58(bytes_string + hash256(bytes_string)[:4])

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


def hash160(sec_message):
    """
    hash160기반으로 메시지의 해시값을 계산하는 함수
    - 비트코인 주소 형식 생성 프로세스의 2단계에 해당
    - SEC 형식의 주소를 sha256과 ripemd160 해시를 연속으로 사용
    :param sec_message: 해시할 SEC 형식 메시지
    :return: 해시값
    """
    return hashlib.new("ripemd160", sha256(sec_message).digest()).digest()


# exercise7 : 리틀엔디언을 읽어 정수로 변환하는 함수
def little_endian_to_int(bytes_str):
    return int.from_bytes(bytes_str, 'little')

# exercise8 : 정수를 리틀엔디언으로 변환하는 함수
def int_to_little_endian(num, length):
    return num.to_bytes(length, "little")


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


def bytes_to_bit_field(some_bytes):
    flag_bits = []
    for byte in some_bytes:
        for _ in range(8):
            flag_bits.append(byte & 1)
            byte >>= 1
    return flag_bits

def bit_field_to_bytes(bit_field):
    """
    비트 필드를 바이트로 변환하는 함수
    :param bit_field: 비트 필드
    :return: 바이트열
    """
    if len(bit_field) % 8 != 0:
        raise RuntimeError('bit_field does not have a length that is divisible by 8')
    result = bytearray(len(bit_field) // 8)
    for i, bit in enumerate(bit_field):
        byte_index, bit_index = divmod(i, 8)
        if bit:
            result[byte_index] |= 1 << bit_index
    return bytes(result)



def murmur3(data, seed=0):
    """
    블룸 필터에서 사용되는 해시함수
    - BIP0037에서는 간단한 구현을 위해 시드만 다른 동일한 해시 함수 사용
    - 암호학적으로 안전하지는 않지만 출력을 빠르게 계산 가능
    - 필터 함수의 요구 사항
        - 출력값이 입력에 의해서만 결정
        - 출력값이 범위 안에서 균등하게 나옴
    :param data: 데이터
    :param seed: 해시 계산에 사용되는 시드
    :return: 해시값
    """
    c1 = 0xcc9e2d51
    c2 = 0x1b873593
    length = len(data)
    h1 = seed
    roundedEnd = (length & 0xfffffffc)  # round down to 4 byte block
    for i in range(0, roundedEnd, 4):
        # little endian load order
        k1 = (data[i] & 0xff) | ((data[i + 1] & 0xff) << 8) | \
            ((data[i + 2] & 0xff) << 16) | (data[i + 3] << 24)
        k1 *= c1
        k1 = (k1 << 15) | ((k1 & 0xffffffff) >> 17)  # ROTL32(k1,15)
        k1 *= c2
        h1 ^= k1
        h1 = (h1 << 13) | ((h1 & 0xffffffff) >> 19)  # ROTL32(h1,13)
        h1 = h1 * 5 + 0xe6546b64
    # tail
    k1 = 0
    val = length & 0x03
    if val == 3:
        k1 = (data[roundedEnd + 2] & 0xff) << 16
    # fallthrough
    if val in [2, 3]:
        k1 |= (data[roundedEnd + 1] & 0xff) << 8
    # fallthrough
    if val in [1, 2, 3]:
        k1 |= data[roundedEnd] & 0xff
        k1 *= c1
        k1 = (k1 << 15) | ((k1 & 0xffffffff) >> 17)  # ROTL32(k1,15)
        k1 *= c2
        h1 ^= k1
    # finalization
    h1 ^= length
    # fmix(h1)
    h1 ^= ((h1 & 0xffffffff) >> 16)
    h1 *= 0x85ebca6b
    h1 ^= ((h1 & 0xffffffff) >> 13)
    h1 *= 0xc2b2ae35
    h1 ^= ((h1 & 0xffffffff) >> 16)
    return h1 & 0xffffffff
