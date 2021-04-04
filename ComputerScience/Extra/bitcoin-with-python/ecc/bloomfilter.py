from ecc.utils import (
    bit_field_to_bytes,
    encode_varint,
    int_to_little_endian,
    murmur3,
)
from ecc.network import GenericMessage

# BIP37에서 제안된 시드를 구할 때 사용하는 상수
BIP37_CONSTANT = 0xfba4c795

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
