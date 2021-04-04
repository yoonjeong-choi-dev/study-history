from ecc.utils import (
    hash256,
    int_to_little_endian,
    little_endian_to_int,
    TWO_WEEKS
)
from ecc.merkle_block import make_merkle_root


GENESIS_BLOCK = bytes.fromhex('0100000000000000000000000000000000000000000000000000000000000000000000003ba3edfd7a7b12b27ac72c3e67768f617fc81bc3888a51323a9fb8aa4b1e5e4a29ab5f49ffff001d1dac2b7c')
TESTNET_GENESIS_BLOCK = bytes.fromhex('0100000000000000000000000000000000000000000000000000000000000000000000003ba3edfd7a7b12b27ac72c3e67768f617fc81bc3888a51323a9fb8aa4b1e5e4adae5494dffff001d1aa4ae18')
LOWEST_BITS = bytes.fromhex('ffff001d')


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
            - 블록의 전체 트랜잭션 해시값들을 대표하는 단일 해시
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

    def __init__(self, version, prev_block, merkle_root, timestamp, bits, nounce, tx_hashes=None):
        self.version = version
        self.prev_block = prev_block
        self.merkle_root = merkle_root
        self.timestamp = timestamp
        self.bits = bits
        self.nounce = nounce
        self.tx_hashes = tx_hashes

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

    def validate_merkle_root(self):
        """
        트랜잭션 해시 리스트와 헤더의 머클루트 정보가 동일한지 확인
        - 풀 노드의 경우 모든 트랜잭션(tx_hashes)의 해시값이 주어짐
            - 각 단말 노드는 리틀엔디언으로 읽어야 한다
            - 리틀엔디언으로 표현된 노드들로 머클 투트를 계산한뒤 다시 리틀엔디언으로 표현
        - 헤더의 머클루트(merkle_root)
        :return: 트랜잭션 리스트를 통해 구한 머클루트와 헤더의 머클루트의 정보가 동일한지 확인
        """
        # 각 단말노드를 리틀엔디언으로 표현
        hashes = [h[::-1] for h in self.tx_hashes]

        # 머클 루트 계산 후 리틀엔디언으로 표현
        merkle_root = make_merkle_root(hashes)[::-1]

        return self.merkle_root == merkle_root
