from ecc.utils import (
    hash256,
    encode_varint,
    int_to_little_endian,
    little_endian_to_int,
    read_varint,
)
from io import BytesIO
import math

def example1():
    hash0 = bytes.fromhex('c117ea8ec828342f4dfb0ad6bd140e03a50720ece40169ee38bdc15d9eb64cf5')
    hash1 = bytes.fromhex('c131474164b412e3406696da1ee20ab0fc9bf41c8f05fa8ceea7a08d672d7cc5')
    parent = hash256(hash0+hash1)
    print(parent.hex())


def make_merkle_parent(hash1, hash2):
    """
    두 노드를 이용하여 머클부모를 반환
    - 말단 노드 : 블록의 트랜잭션 해시값
    :param hash1: 왼쪽 자식 노드
    :param hash2: 오른쪽 자식 노드
    :return: 머클 부모(부모 해시값)
    """
    return hash256(hash1+hash2)


def exercise1():
    tx_hash0 = bytes.fromhex('c117ea8ec828342f4dfb0ad6bd140e03a50720ece40169ee38bdc15d9eb64cf5')
    tx_hash1 = bytes.fromhex('c131474164b412e3406696da1ee20ab0fc9bf41c8f05fa8ceea7a08d672d7cc5')
    parent = make_merkle_parent(tx_hash0, tx_hash1)

    answer = bytes.fromhex('8b30c5ba100f6f2e5ad1e2a742e5020491240f8eb514fe97c713c31718ad7ecd')
    print("Merkle Parent : {}".format(parent==answer))


def example2():
    hex_hashes = [
        'c117ea8ec828342f4dfb0ad6bd140e03a50720ece40169ee38bdc15d9eb64cf5',
        'c131474164b412e3406696da1ee20ab0fc9bf41c8f05fa8ceea7a08d672d7cc5',
        'f391da6ecfeed1814efae39e7fcb3838ae0b02c02ae7d0a5848a66947c0727b0',
        '3d238a92a94532b946c90e19c49351c763696cff3db400485b813aecb8a13181',
        '10092f2633be5f3ce349bf9ddbde36caa3dd10dfa0ec8106bce23acbff637dae',
    ]

    hashes = [bytes.fromhex(x) for x in hex_hashes]

    if len(hashes) %2 ==1:
        hashes.append(hashes[-1])

    parent_level = []
    for i in range(0, len(hashes), 2):
        parent = make_merkle_parent(hashes[i], hashes[i+1])
        parent_level.append(parent)

    for item in parent_level:
        print(item.hex())


def make_merkle_parent_level(hashes):
    """
    블록의 트랜잭션 해시값으로 구성된 리스트를 이용하여 머클 부모 레벨을 생성하는 함수
    - 머클 부모 레벨
        : 리스트의 모든 해시값에 대해 부모 해시를 구함
    - 길이가 홀수인 경우, 마지막 해시값을 리스트에 추가하여 짝수로 만든다
    :param hashes: 블록의 트랜잭션 해시값으로 구성된 리스트
    :return: 머클 부모 레벨 리스트
    """
    if len(hashes) == 1:
        raise RuntimeError('Cannot take a parent level with only 1 item')

    if len(hashes) %2 ==1:
        hashes.append(hashes[-1])

    parent_level = []
    for i in range(0, len(hashes), 2):
        parent = make_merkle_parent(hashes[i], hashes[i+1])
        parent_level.append(parent)

    return parent_level


def exercise2():
    hex_hashes = [
        'c117ea8ec828342f4dfb0ad6bd140e03a50720ece40169ee38bdc15d9eb64cf5',
        'c131474164b412e3406696da1ee20ab0fc9bf41c8f05fa8ceea7a08d672d7cc5',
        'f391da6ecfeed1814efae39e7fcb3838ae0b02c02ae7d0a5848a66947c0727b0',
        '3d238a92a94532b946c90e19c49351c763696cff3db400485b813aecb8a13181',
        '10092f2633be5f3ce349bf9ddbde36caa3dd10dfa0ec8106bce23acbff637dae',
        '7d37b3d54fa6a64869084bfd2e831309118b9e833610e6228adacdbd1b4ba161',
        '8118a77e542892fe15ae3fc771a4abfd2f5d5d5997544c3487ac36b5c85170fc',
        'dff6879848c2c9b62fe652720b8df5272093acfaa45a43cdb3696fe2466a3877',
        'b825c0745f46ac58f7d3759e6dc535a1fec7820377f24d4c2c6ad2cc55c0cb59',
        '95513952a04bd8992721e9b7e2937f1c04ba31e0469fbe615a78197f68f52b7c',
        '2e6d722e5e4dbdf2447ddecc9f7dabb8e299bae921c99ad5b0184cd9eb8e5908',
    ]
    tx_hashes = [bytes.fromhex(x) for x in hex_hashes]

    tx_merkle_parent_level = make_merkle_parent_level(tx_hashes)

    answers_hex = [
        '8b30c5ba100f6f2e5ad1e2a742e5020491240f8eb514fe97c713c31718ad7ecd',
        '7f4e6f9e224e20fda0ae4c44114237f97cd35aca38d83081c9bfd41feb907800',
        'ade48f2bbb57318cc79f3a8678febaa827599c509dce5940602e54c7733332e7',
        '68b3e2ab8182dfd646f13fdf01c335cf32476482d963f5cd94e934e6b3401069',
        '43e7274e77fbe8e5a42a8fb58f7decdb04d521f319f332d88e6b06f8e6c09e27',
        '1796cd3ca4fef00236e07b723d3ed88e1ac433acaaa21da64c4b33c946cf3d10',
    ]
    answers = [bytes.fromhex(x) for x in answers_hex]

    print("Merkle Parent Level : {}".format(tx_merkle_parent_level == answers))


def make_merkle_root(hashes):
    """
    블록의 트랜잭션 해시값으로 구성된 리스트를 이용하여 머클 루트를 생성하는 함수
    - 머클 루트
        - 머클 트리의 루트 노드
        - 전체 트랜잭션 해시값들을 대표하는 단일 해시
    :param hashes: 블록의 트랜잭션 해시값으로 구성된 리스트
    :return: 머클 루트(해시)
    """
    current_parent_level = hashes

    # 머클부모 레벨의 길이가 1개일 때까지 반복
    while len(current_parent_level) > 1:
        current_parent_level = make_merkle_parent_level(current_parent_level)

    return current_parent_level[0]

def exercise3():
    hex_hashes = [
        'c117ea8ec828342f4dfb0ad6bd140e03a50720ece40169ee38bdc15d9eb64cf5',
        'c131474164b412e3406696da1ee20ab0fc9bf41c8f05fa8ceea7a08d672d7cc5',
        'f391da6ecfeed1814efae39e7fcb3838ae0b02c02ae7d0a5848a66947c0727b0',
        '3d238a92a94532b946c90e19c49351c763696cff3db400485b813aecb8a13181',
        '10092f2633be5f3ce349bf9ddbde36caa3dd10dfa0ec8106bce23acbff637dae',
        '7d37b3d54fa6a64869084bfd2e831309118b9e833610e6228adacdbd1b4ba161',
        '8118a77e542892fe15ae3fc771a4abfd2f5d5d5997544c3487ac36b5c85170fc',
        'dff6879848c2c9b62fe652720b8df5272093acfaa45a43cdb3696fe2466a3877',
        'b825c0745f46ac58f7d3759e6dc535a1fec7820377f24d4c2c6ad2cc55c0cb59',
        '95513952a04bd8992721e9b7e2937f1c04ba31e0469fbe615a78197f68f52b7c',
        '2e6d722e5e4dbdf2447ddecc9f7dabb8e299bae921c99ad5b0184cd9eb8e5908',
        'b13a750047bc0bdceb2473e5fe488c2596d7a7124b4e716fdd29b046ef99bbf0',
    ]
    tx_hashes = [bytes.fromhex(x) for x in hex_hashes]

    tx_root = make_merkle_root(tx_hashes)

    answer_hex = 'acbcab8bcc1af95d8d563b77d24c3d19b18f1486383d75a5085c4e86c86beed6'
    answer = bytes.fromhex(answer_hex)

    print("Merkle root : {}".format(tx_root==answer))



from ecc.block import bits_to_target

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


def exercise4():
    hashes_hex = [
        'f54cb69e5dc1bd38ee6901e4ec2007a5030e14bdd60afb4d2f3428c88eea17c1',
        'c57c2d678da0a7ee8cfa058f1cf49bfcb00ae21eda966640e312b464414731c1',
        'b027077c94668a84a5d0e72ac0020bae3838cb7f9ee3fa4e81d1eecf6eda91f3',
        '8131a1b8ec3a815b4800b43dff6c6963c75193c4190ec946b93245a9928a233d',
        'ae7d63ffcb3ae2bc0681eca0df10dda3ca36dedb9dbf49e33c5fbe33262f0910',
        '61a14b1bbdcdda8a22e61036839e8b110913832efd4b086948a6a64fd5b3377d',
        'fc7051c8b536ac87344c5497595d5d2ffdaba471c73fae15fe9228547ea71881',
        '77386a46e26f69b3cd435aa4faac932027f58d0b7252e62fb6c9c2489887f6df',
        '59cbc055ccd26a2c4c4df2770382c7fea135c56d9e75d3f758ac465f74c025b8',
        '7c2bf5687f19785a61be9f46e031ba041c7f93e2b7e9212799d84ba052395195',
        '08598eebd94c18b0d59ac921e9ba99e2b8ab7d9fccde7d44f2bd4d5e2e726d2e',
        'f0bb99ef46b029dd6f714e4b12a7d796258c48fee57324ebdc0bbc4700753ab1',
    ]
    hashes = [bytes.fromhex(x) for x in hashes_hex]
    stream = BytesIO(bytes.fromhex(
        '00000020fcb19f7895db08cadc9573e7915e3919fb76d59868a51d995201000000000000acbcab8bcc1af95d8d563b77d24c3d19b18f1486383d75a5085c4e86c86beed691cfa85916ca061a00000000'))
    block = Block.parse(stream)
    block.tx_hashes = hashes

    print("Validate Merkle Root : {}".format(block.validate_merkle_root()))


def exercise5():
    import math
    total = 27
    max_depth = math.ceil(math.log(total, 2))

    merkle_tree = []
    cur_num = 0
    for depth in range(max_depth+1):
        num_items = math.ceil(total/2**(max_depth - depth))
        level_hash = []
        for _ in range(num_items):
            level_hash.append(cur_num)
            cur_num += 1
        merkle_tree.append(level_hash)

    for level in merkle_tree:
        print(level)



class MerkleTree:
    """
    풀노드가 라이트노드에게 포함증명을 보낼 때 함께 보내는 정보
        - 머클트리의 구조
        - 머클트리에서 어떤 해시값이 어느 위치에 있는지에 대한 정보
        => 두 정보를 바탕으로 라이트 노드는 머클트리를 부분적으로 재구성하여 머클루트 계산 및 포함 증명 확인

    """
    def __init__(self, total):
        # 단말 노드의 개수
        self.total = total
        # 트리의 깊이 : 매 레벨마다 노드의 수가 절반씩 줄어든다
        self.max_depth = math.ceil(math.log(total, 2))

        # 머클 트리는 완전 이진트리
        # => 각 레벨에 있는 노드들을 배열로 표현
        self.nodes = []
        for depth in range(self.max_depth+1):
            num_items = math.ceil(total / 2 ** (self.max_depth - depth))
            level_hash = [None] * num_items
            self.nodes.append(level_hash)

        # dfs로 비어 있는 노드의 해시값을 계산할 때 사용 : 현재 레벨과 현재 인덱스
        self.current_depth = 0
        self.current_index = 0

    def __repr__(self):
        ret = []
        for depth, level in enumerate(self.nodes):
            items = []
            for idx, h in enumerate(level):
                if h is None:
                    short = "None"
                else:
                    short = "{}...".format(h.hex()[:8])

                if depth == self.current_depth and idx == self.current_index:
                    items.append("*{}*".format(short[:-2]))
                else:
                    items.append("{}".format(short))
            ret.append(", ".join(items))

        return "\n".join(ret)

    """
    트리의 노드를 채우기 위해 필요한 연산
    - 트리 순회를 위한 노드 이동 연산
        - up : 부모 노드로 이동
        - left : 왼쪽 자식 노드로 이동
        - right : 오른쪽 자식 노드로 이동
    - 현재 방문하는 노드의 getter/setter 
        - set_current_node 
        - get_current_node
        - get_left_node
        - get_right_node
    - 현재 방문하는 노드의 정보
        - is_leaf : 리프 노드 여부
        - right_exists : 오른쪽 자식 노드 유무
    """
    def up(self):
        self.current_depth -= 1
        self.current_index //= 2
        
    def left(self):
        self.current_depth += 1
        self.current_index *= 2
        
    def right(self):
        self.current_depth += 1
        self.current_index = self.current_index*2 + 1
        
    def root(self):
        return self.nodes[0][0]
    
    def set_current_node(self, value):
        self.nodes[self.current_depth][self.current_index] = value
        
    def get_current_node(self):
        return self.nodes[self.current_depth][self.current_index]
    
    def get_left_node(self):
        return self.nodes[self.current_depth + 1][self.current_index * 2]
        
    def get_right_node(self):
        return self.nodes[self.current_depth + 1][self.current_index*2 + 1]
    
    def is_leaf(self):
        return self.current_depth == self.max_depth
    
    def right_exists(self):
        return len(self.nodes[self.current_depth + 1]) > self.current_index *2 + 1

    """
    플래그 비트를 사용하여 방문 노드와 머클블록에 있는 해시값을 대응
        : 플래그비트 작성 규칙
    - 비트 0
        - 노드의 해시값이 머클블록 hashes 필드에 있는 경우
        i.e 해시값이 머클블록을 통해 알 수 있는 노드
    - 비트 1
        - 라이트 노드가 계산해야하는 내부 노드인 경우
        - 블록 포함 여부가 궁금한 관심 트랜잭션에 해당하는 단말 노드인 경우
        i.e 계산이 필요하거나 관심이 있는 노드
    - dfs 순서로 주어진다
    """
    def populate_tree(self, flag_bits, hashes):
        # 머클루트가 계산될 때까지 dfs
        while self.root() is None:
            # 단말 노드인 경우 해시값은 항상 주어진다
           if self.is_leaf():
                flag_bits.pop(0)    # 항상 주어지기 때문에 필요없는 비트
                self.set_current_node(hashes.pop(0))
                self.up()   # 해시값 설정 후 부모 노드로 올라간다
           else:
                left_hash = self.get_left_node()
                # 왼쪽 자식 노드가 None인 경우 : 해시값이 주어지거나, 계산 필요
                if left_hash is None:
                    # 해시값이 있는 경우
                    if flag_bits.pop(0) == 0:
                        self.set_current_node(hashes.pop(0))
                        self.up()
                    # dfs 순회를 통해 계산 필요
                    else:
                        self.left()
                # 오른쪽 자식이 있는 경우 : 두 자식 노드를 통해 부모 머클 노드 계산
                elif self.right_exists():
                    right_hash = self.get_right_node()
                    # 오른쪽 자식 계산 필요
                    if right_hash is None:
                        self.right()
                    else:
                        self.set_current_node(make_merkle_parent(left_hash, right_hash))
                        self.up()
                # 왼쪽 자식만 있는 경우 : 왼쪽 자식을 복사하여 부모 머클 노드 계산
                else:
                    self.set_current_node(make_merkle_parent(left_hash, left_hash))
                    self.up()

        # 검증 : 모든 해시를 사용하였는지
        if len(hashes) != 0:
            raise RuntimeError("hashes not all consumed {}".format(len(hashes)))

        # 검증 : 모든 플래그비트를 사용하였는지
        for flag_bit in flag_bits:
            if flag_bit != 0:
                raise RuntimeError("flag bits not all consumed")







def example3():
    hex_hashes = [
        "9745f7173ef14ee4155722d1cbf13304339fd00d900b759c6f9d58579b5765fb",
        "5573c8ede34936c29cdfdfe743f7f5fdfbd4f54ba0705259e62f39917065cb9b",
        "82a02ecbb6623b4274dfcab82b336dc017a27136e08521091e443e62582e8f05",
        "507ccae5ed9b340363a0e6d765af148be9cb1c8766ccc922f83e4ae681658308",
        "a7a4aec28e7162e1e9ef33dfa30f0bc0526e6cf4b11a576f6c5de58593898330",
        "bb6267664bd833fd9fc82582853ab144fece26b7a8a5bf328f8a059445b59add",
        "ea6d7ac1ee77fbacee58fc717b990c4fcccf1b19af43103c090f601677fd8836",
        "457743861de496c429912558a106b810b0507975a49773228aa788df40730d41",
        "7688029288efc9e9a0011c960a6ed9e5466581abf3e3a6c26ee317461add619a",
        "b1ae7f15836cb2286cdd4e2c37bf9bb7da0a2846d06867a429f654b2e7f383c9",
        "9b74f89fa3f93e71ff2c241f32945d877281a6a50a6bf94adac002980aafe5ab",
        "b3a92b5b255019bdaf754875633c2de9fec2ab03e6b8ce669d07cb5b18804638",
        "b5c0b915312b9bdaedd2b86aa2d0f8feffc73a2d37668fd9010179261e25e263",
        "c9d52c5cb1e557b92c84c52e7c4bfbce859408bedffc8a5560fd6e35e10b8800",
        "c555bc5fc3bc096df0a0c9532f07640bfb76bfe4fc1ace214b8b228a1297a4c2",
        "f9dbfafc3af3400954975da24eb325e326960a25b87fffe23eef3e7ed2fb610e",
    ]
    tree = MerkleTree(len(hex_hashes))
    tree.nodes[4] = [bytes.fromhex(h) for h in hex_hashes]
    tree.nodes[3] = make_merkle_parent_level(tree.nodes[4])
    tree.nodes[2] = make_merkle_parent_level(tree.nodes[3])
    tree.nodes[1] = make_merkle_parent_level(tree.nodes[2])
    tree.nodes[0] = make_merkle_parent_level(tree.nodes[1])

    print(tree)


def bytes_to_bit_field(some_bytes):
    flag_bits = []
    for byte in some_bytes:
        for _ in range(8):
            flag_bits.append(byte & 1)
            byte >>= 1
    return flag_bits


class MerkleBlock:
    """
    머클 블록
    - 풀 노드에서 라이트노드에게 보내는 포함 증명과 관련된 정보를 구성하는 블록
    - 블록 헤더 정보 + 포함 증명 으로 구성
    - 블록 헤더 정보
        - 블록 버전(정수, 4바이트 리틀엔디언)
        - 이전 블록 해시값(바이트, 32바이트 리틀엔디언)
        - 머클루트(바이트, 32바이트 리틀엔디언)
        - 타임스탬프(정수, 4바이트 리틀엔디언)
        - 비트값(바이트, 4바이트)
        - 논스값(바이트, 4바이트)
    - 포함 증명
        - 모든 트랜잭션의 갯수
            - 4바이트 리틀엔디언
            - 머클 트리의 단말 노드 개수
            - 해당 정보를 통해 라이트 노드는 초기 머클트리 구성
        - 해시값 개수
            - 가변 정수 : 개수 + 개수*(32바이트 리틀엔디언)
            - 풀 노드에서 전송하는 머클트리의 노드들의 해시값들
        - 플래그 비트
            - 가변 정수 : 개수 + 개수*1바이트
            - 머클트리에서 해시값의 위치 정보
              => 머클트리 dfs에서 방문하는 노드와 해시값을 대응시켜주는 역할
            - 8비트씩 묶어 바이트로 인코딩
    """

    def __init__(self, version, prev_block, merkle_root, timestamp, bits, nonce, total, hashes, flags):
        self.version = version
        self.prev_block = prev_block
        self.merkle_root = merkle_root
        self.timestamp = timestamp
        self.bits = bits
        self.nonce = nonce
        self.total = total
        self.hashes = hashes
        self.flags = flags

    def __repr__(self):
        ret = '{}\n'.format(self.total)
        for h in self.hashes:
            ret += '\t{}\n'.format(h.hex())
        ret += '{}'.format(self.flags.hex())
        return ret

    @classmethod
    def parse(cls, stream):
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

        # 전체 트랜잭션 갯수
        total = little_endian_to_int(stream.read(4))

        # 해시값 : 가변 정수 및 32바이트 리틀엔디언
        num_hashes = read_varint(stream)
        hashes = []
        for _ in range(num_hashes):
            hashes.append(stream.read(32)[::-1])

        # 플래그 비트 : 가변 정수 및 1바이트
        num_flags = read_varint(stream)
        flag_bits = stream.read(num_flags)

        return cls(version, prev_block, merkle_root, timestamp, bits,
                   nounce, total, hashes, flag_bits)


    def is_valid(self):
        # 머클 루트 계산
        flag_bits = bytes_to_bit_field(self.flags)
        hashes = [h[::-1] for h in self.hashes]

        # 머클 트리 객체 생성 및 루트 계산
        merkle_tree = MerkleTree(self.total)
        merkle_tree.populate_tree(flag_bits, hashes)

        merkle_root = merkle_tree.root()[::-1]
        return merkle_root == self.merkle_root



def exercise6():
    def assertEqual(title, my_sol, ans):
        print("{} : {}".format(title, my_sol==ans))

    hex_merkle_block = '00000020df3b053dc46f162a9b00c7f0d5124e2676d47bbe7c5d0793a500000000000000ef445fef2ed495c275892206ca533e7411907971013ab83e3b47bd0d692d14d4dc7c835b67d8001ac157e670bf0d00000aba412a0d1480e370173072c9562becffe87aa661c1e4a6dbc305d38ec5dc088a7cf92e6458aca7b32edae818f9c2c98c37e06bf72ae0ce80649a38655ee1e27d34d9421d940b16732f24b94023e9d572a7f9ab8023434a4feb532d2adfc8c2c2158785d1bd04eb99df2e86c54bc13e139862897217400def5d72c280222c4cbaee7261831e1550dbb8fa82853e9fe506fc5fda3f7b919d8fe74b6282f92763cef8e625f977af7c8619c32a369b832bc2d051ecd9c73c51e76370ceabd4f25097c256597fa898d404ed53425de608ac6bfe426f6e2bb457f1c554866eb69dcb8d6bf6f880e9a59b3cd053e6c7060eeacaacf4dac6697dac20e4bd3f38a2ea2543d1ab7953e3430790a9f81e1c67f5b58c825acf46bd02848384eebe9af917274cdfbb1a28a5d58a23a17977def0de10d644258d9c54f886d47d293a411cb6226103b55635'
    mb = MerkleBlock.parse(BytesIO(bytes.fromhex(hex_merkle_block)))

    merkle_root_hex = 'ef445fef2ed495c275892206ca533e7411907971013ab83e3b47bd0d692d14d4'
    merkle_root = bytes.fromhex(merkle_root_hex)[::-1]
    assertEqual("merkle root", mb.merkle_root, merkle_root)

    prev_block_hex = 'df3b053dc46f162a9b00c7f0d5124e2676d47bbe7c5d0793a500000000000000'
    prev_block = bytes.fromhex(prev_block_hex)[::-1]
    assertEqual("previous block", mb.prev_block, prev_block)

    timestamp = little_endian_to_int(bytes.fromhex('dc7c835b'))
    assertEqual("time stamp", mb.timestamp, timestamp)

    bits = bytes.fromhex('67d8001a')
    assertEqual("bits", mb.bits, bits)

    nonce = bytes.fromhex('c157e670')
    assertEqual("nonce", mb.nonce, nonce)

    total = little_endian_to_int(bytes.fromhex('bf0d0000'))
    assertEqual("total transactions", mb.total, total)

    hex_hashes = [
        'ba412a0d1480e370173072c9562becffe87aa661c1e4a6dbc305d38ec5dc088a',
        '7cf92e6458aca7b32edae818f9c2c98c37e06bf72ae0ce80649a38655ee1e27d',
        '34d9421d940b16732f24b94023e9d572a7f9ab8023434a4feb532d2adfc8c2c2',
        '158785d1bd04eb99df2e86c54bc13e139862897217400def5d72c280222c4cba',
        'ee7261831e1550dbb8fa82853e9fe506fc5fda3f7b919d8fe74b6282f92763ce',
        'f8e625f977af7c8619c32a369b832bc2d051ecd9c73c51e76370ceabd4f25097',
        'c256597fa898d404ed53425de608ac6bfe426f6e2bb457f1c554866eb69dcb8d',
        '6bf6f880e9a59b3cd053e6c7060eeacaacf4dac6697dac20e4bd3f38a2ea2543',
        'd1ab7953e3430790a9f81e1c67f5b58c825acf46bd02848384eebe9af917274c',
        'dfbb1a28a5d58a23a17977def0de10d644258d9c54f886d47d293a411cb62261',
    ]
    hashes = [bytes.fromhex(h)[::-1] for h in hex_hashes]
    assertEqual("hashes", mb.hashes, hashes)

    flags = bytes.fromhex('b55635')
    assertEqual("bit flags", mb.flags, flags)

def exercise7():
    hex_merkle_block = '00000020df3b053dc46f162a9b00c7f0d5124e2676d47bbe7c5d0793a500000000000000ef445fef2ed495c275892206ca533e7411907971013ab83e3b47bd0d692d14d4dc7c835b67d8001ac157e670bf0d00000aba412a0d1480e370173072c9562becffe87aa661c1e4a6dbc305d38ec5dc088a7cf92e6458aca7b32edae818f9c2c98c37e06bf72ae0ce80649a38655ee1e27d34d9421d940b16732f24b94023e9d572a7f9ab8023434a4feb532d2adfc8c2c2158785d1bd04eb99df2e86c54bc13e139862897217400def5d72c280222c4cbaee7261831e1550dbb8fa82853e9fe506fc5fda3f7b919d8fe74b6282f92763cef8e625f977af7c8619c32a369b832bc2d051ecd9c73c51e76370ceabd4f25097c256597fa898d404ed53425de608ac6bfe426f6e2bb457f1c554866eb69dcb8d6bf6f880e9a59b3cd053e6c7060eeacaacf4dac6697dac20e4bd3f38a2ea2543d1ab7953e3430790a9f81e1c67f5b58c825acf46bd02848384eebe9af917274cdfbb1a28a5d58a23a17977def0de10d644258d9c54f886d47d293a411cb6226103b55635'
    mb = MerkleBlock.parse(BytesIO(bytes.fromhex(hex_merkle_block)))
    print("Merkle root valid : {}".format(mb.is_valid()))


if __name__ == "__main__":
    print("Chapter 11. Simplified Payment Verification")
    #example1()
    #exercise1()
    #example2()
    #exercise2()
    #exercise3()
    #exercise4()
    #exercise5()
    #example3()
    #exercise6()
    exercise7()