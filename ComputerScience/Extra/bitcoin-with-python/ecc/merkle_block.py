from ecc.utils import (
    hash256,
    little_endian_to_int,
    read_varint,
)
import math


def make_merkle_parent(hash1, hash2):
    """
    두 노드를 이용하여 머클부모를 반환
    - 말단 노드 : 블록의 트랜잭션 해시값
    :param hash1: 왼쪽 자식 노드
    :param hash2: 오른쪽 자식 노드
    :return: 머클 부모(부모 해시값)
    """
    return hash256(hash1+hash2)

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
        for depth in range(self.max_depth + 1):
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
        self.current_index = self.current_index * 2 + 1

    def root(self):
        return self.nodes[0][0]

    def set_current_node(self, value):
        self.nodes[self.current_depth][self.current_index] = value

    def get_current_node(self):
        return self.nodes[self.current_depth][self.current_index]

    def get_left_node(self):
        return self.nodes[self.current_depth + 1][self.current_index * 2]

    def get_right_node(self):
        return self.nodes[self.current_depth + 1][self.current_index * 2 + 1]

    def is_leaf(self):
        return self.current_depth == self.max_depth

    def right_exists(self):
        return len(self.nodes[self.current_depth + 1]) > self.current_index * 2 + 1

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
                flag_bits.pop(0)  # 항상 주어지기 때문에 필요없는 비트
                self.set_current_node(hashes.pop(0))
                self.up()  # 해시값 설정 후 부모 노드로 올라간다
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
