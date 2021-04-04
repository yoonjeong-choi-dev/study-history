from ecc.utils import (
    hash256,
    hash160,
    int_to_little_endian,
    encode_varint
)

def example1():
    bit_field_size = 10
    bit_field = [0] * bit_field_size

    # 해시 + 나머지연산 이용
    h = hash256(b"hello world")
    bit = int.from_bytes(h, "big") % bit_field_size

    bit_field[bit] = 1
    print(bit_field)


def exercise1():
    bit_field_size = 10
    bit_field = [0] * bit_field_size

    words = [b"hello world", b"goodbye"]
    for word in words:
        h = hash160(word)
        bit = int.from_bytes(h, "big") % bit_field_size
        bit_field[bit] = 1

    print(bit_field)


def example2():
    bit_field_size = 10
    bit_field = [0] * bit_field_size

    words = [b"hello world", b"goodbye"]
    hash_functions = [hash256, hash160]
    for word in words:
        for hash_function in hash_functions:
            h = hash_function(word)
            bit = int.from_bytes(h, "big") % bit_field_size
            bit_field[bit] = 1

    print(bit_field)




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


# BIP37에서 제안된 시드를 구할 때 사용하는 상수
BIP37_CONSTANT = 0xfba4c795

def example3():
    field_size = 2
    num_functions = 2
    tweak = 42  # 시드를 조정하기 위한 엔트로피

    bit_field_size = field_size * 8
    bit_field = [0]*bit_field_size

    words = [b"hello world", b"goodbye"]
    for word in words:
        for i in range(num_functions):
            seed = i * BIP37_CONSTANT + tweak
            h = murmur3(word, seed)
            bit = h % bit_field_size
            bit_field[bit] = 1

    print(bit_field)



class BloomFilter:
    """
    블룸 필터
    - 단순 지급 검증의 문제점
        - 풀 노드는 라이트 노드의 관심 트랜잭션에 대한 포함 증명 제공
          => 풀 노드는 라이트 노드의 관심 트랜잭션을 알게 된다
        - 라이트 노드의 개인 정보가 노출
    - 단순 지급 검증 해결 방법
        : 관심 트랜잭션을 포함한 더 많은 트랜잭션이 있는 상위 집합을 알려준다
    - 블룸 필러는 상위 집합에 포함되는 트랜잭션을 선정하는 필터
        - 어떤 집합의 원소를 정해진 개수의 그룹 중 1개의 그룹에 대응시키는 함수
        - 풀 노드는 블룸 필터를 통해 트랜잭션을 선별하고, 선별된 트랜잭션을 라이트 노드에게 전송
        - 트랜잭션을 그룹으로 나누기 위해 해시함수 + 나머지연산 활용
    - 블룸 필터의 구성 요소
        - 비트 필드의 길이
        - 사용하는 해시 함수들
            - 다수의 해시 함수를 이용하면 비트 필드의 길이를 줄일 수 있음
            - 해시 함수마다 1개의 비트가 결정
            - 길이가 n이고, 해시함수 개수가 m인 경우, nCm(n choose m)개의 그룹 표현 가능
        - 관심 대상 그룹을 표시하는 비트 필드
    - BIP0037 블룸 필터
        - 비트 필드의 길이(바이트 단위) 또는 그룹의 개수
        - 해시 함수의 개수
            - 해시 함수는 시드만 다른 동일 해시함수 murmur3 사용
        - tweak 파라미터
            - 시드 계산 시 사용 : i*BIP37_CONSTANT + tweak
            - 시드값을 조정하기 위해 더해질 수 있는 일종의 엔트로피
        - 설계된 블룸 필터의 비트 필드 값
    """
    def __init__(self, size, function_count ,tweak):
        self.size = size
        self.bit_field = [0] * (size*8)
        self.function_count = function_count
        self.tweak = tweak

    def filter_bytes(self):
        """
        비트 필드를 바이트열로 변환하는 함수
        """
        return bit_field_to_bytes(self.bit_field)

    def add(self, item):
        """
        인자로 받은 요소를 블룸 필터에 추가하는 함수
        - 각 필터 함수로 계산한 비트 위치에 1을 설정
        :param item: 블룸 필터에 추가할 요소
        """
        for i in range(self.function_count):
            seed = i * BIP37_CONSTANT + self.tweak
            h = murmur3(item, seed)
            # 비트 필드의 길이는 바이트 단위
            bit = h % (self.size*8)
            self.bit_field[bit] = 1

    def filerload(self, flag=1):
        """
        필터로드 메시지의 페이로드로 직렬화하여 메시지를 생성하는 함수
        - 라이트 노드가 블룸 필터를 생성 후, 이 블룸 필터를 풀 노드에 전송해야함
        - 풀 노드에게 보내는 VersionMessage의 렐레이 필드 값을 0으로 설정
            - 풀 노드는 블룸 필터를 수신 받기 전까지 트랜잭션 메세지를 전송하지 않음
            - 풀 노드로 전송하기 위한 블룸 필터 메시지 생성 필요
        :param flag: 비트 필드 업데이트 플래그
            - 0 : 풀 노드는 동작 중 비트 필드 업데이트 x
            - 1,2 : 특정 조건하에 새로운 입력을 필터에 더해 비트 필드 업데이트
        :return: 직렬화한 페이로드를 담고 있는 GenericMessage 객체
        """
        # 비트 필드의 길이 정보 가변 정수 형식
        payload = encode_varint(self.size)

        # 비트 필드 정보
        payload += self.filter_bytes()

        # 해시 함수 개수 : 4바이트 리틀엔디언
        payload += int_to_little_endian(self.function_count, 4)

        # tweak 정보 : 4바이트 리틀엔디언
        payload += int_to_little_endian(self.tweak, 4)

        # matched item flag : 1 바이트 리틀엔디언
        payload += int_to_little_endian(flag, 1)

        return GenericMessage(b"filterload", payload)


def bit_field_to_bytes(bit_field):
    """
    비트 필드를 바이트로 변환하는 함수
    :param bit_field: 비트 필드
    :return: 바이트
    """
    if len(bit_field) % 8 != 0:
        raise RuntimeError('bit_field does not have a length that is divisible by 8')
    result = bytearray(len(bit_field) // 8)
    for i, bit in enumerate(bit_field):
        byte_index, bit_index = divmod(i, 8)
        if bit:
            result[byte_index] |= 1 << bit_index
    return bytes(result)


def exercise2():
    field_size = 10
    num_functions = 5
    tweak = 99  # 시드를 조정하기 위한 엔트로피

    bit_field_size = field_size * 8
    bit_field = [0] * bit_field_size

    words = [b"Hello world", b"Goodbye!"]
    for word in words:
        for i in range(num_functions):
            seed = i * BIP37_CONSTANT + tweak
            h = murmur3(word, seed)
            bit = h % bit_field_size
            bit_field[bit] = 1

    print(bit_field_to_bytes(bit_field).hex())


def exercise3():
    bf = BloomFilter(10, 5, 99)
    items = [b'Hello World', b'Goodbye!']

    answers_hex = ['0000000a080000000140', '4000600a080000010940']

    for i, item in enumerate(items):
        bf.add(item)
        print("{} added : {}".format(item, bf.filter_bytes().hex()==answers_hex[i]))


class GenericMessage:
    """
    일반적인 메시지를 담은 커맨드에 대한 파싱
    """
    def __init__(self, command, payload):
        self.command = command
        self.payload = payload

    def serialize(self):
        return self.payload


def exercise4():
    bf = BloomFilter(10, 5, 99)
    items = [b'Hello World', b'Goodbye!']

    for item in items:
        bf.add(item)

    filterload_message = bf.filerload().serialize()
    answer = '0a4000600a080000010940050000006300000001'
    print("filterload message : {}".format(filterload_message.hex() == answer))


TX_DATA_TYPE = 1
BLOCK_DATA_TYPE = 2
FILTERED_BLOCK_DATA_TYPE = 3
COMPACT_BLOCK_DATA_TYPE = 4

class GetDataMessage:
    """
    특정 블록이나 트랜잭션을 요청하는 커맨드
    - 요청하는 데이터의 유형
        - 요청하는 데이터의 유형 정보를 함께 전송
    - 라이트 노드가 필요로 하는 커맨드
        - 풀 노드에게 관심 트랜잭션이 포함된 머클블록을 요청하는 커맨드
        - 라이트 노드가 요청하는 데이터 유형은 filtered block
            : 라이트 노드가 전송한 블룸 필터를 통과한 트랜잭션을 머클블록의 형태로 전송할 것을 요청
    - 메시지 페이로드 형식
        - 요청하는 항목의 개수
            - 가변 정수 형식
            - 각 항목은 (유형, 항목을 특정하는 해시 식별자)로 구성
        - 각 항목에 대한 유형
            - 4바이트 리틀 엔디언
            - 트랜잭션(1), 일반 블록(2), 머클블록(3), 압축블록(4)
        - 각 항목을 특정하는 해시 식별자
            - 리틀엔디언
            - 트랙잭션 해시(1), 블록 헤더 해시(2,3)
    """
    command = b'getdata'

    def __init__(self):
        self.data = []

    def add_data(self, data_type, identifier):
        self.data.append((data_type, identifier))

    def serialize(self):
        # 요청하는 항목의 개수 : 가변 정수 형식
        payload = encode_varint(len(self.data))

        # 각 항목은 (유형, 항목을 특정하는 해시 식별자)로 구성
        for data_type, identifier in self.data:
            # 유형 : 4바이트 리틀 엔디언
            payload += int_to_little_endian(data_type, 4)
            # 해시 식별자 : 리틀 엔디언
            payload += identifier[::-1]

        return payload


def exercise5():
    get_data = GetDataMessage()

    blocks = [
        bytes.fromhex('00000000000000cac712b726e4326e596170574c01a16001692510c44025eb30'),
        bytes.fromhex('00000000000000beb88910c46f6b442312361c6693a7fb52065b583979844910')
    ]

    for block in blocks:
        get_data.add_data(FILTERED_BLOCK_DATA_TYPE, block)

    payload = get_data.serialize()
    answer_hex = '020300000030eb2540c41025690160a1014c577061596e32e426b712c7ca00000000000000030000001049847939585b0652fba793661c361223446b6fc41089b8be00000000000000'

    print("getdata message : {}".format(payload.hex() == answer_hex))



if __name__ == "__main__":
    print("Chapter 12. Bloom Filter")
    #example1()
    #exercise1()
    #example2()
    #example3()
    #exercise2()
    #exercise3()
    #exercise4()
    exercise5()
