"""
공개키 암호를 위한 타원 곡선의 매개변수
- 타원 곡선 정보
    :  y^2 = x^3 + ax + b 에서 a와 b
- 유한체 정보
    : 유한체의 위수(order)인 소수 p
    => F_p(p:prime) 유한체만 다룬다
- 유한군 정보
    - 유한군을 생성하는 생성점의 x와 y좌표(gx, gy)
    - 해당 유한군의 위수 i.e order of generator

secp256k1
- 비트코인에서 사용하는 모델
- 타원 곡선 정보
    : y^2 = x^3 + 7
- 유한체의 위수
    : 2**256 - 2**32 - 977
- 유한군 생성점
    - x : 0x79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798
    - y : 0x483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8
- 유한군 위수
    : 0xfffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141

S256Field
- secp256k1 모델에서 사용하는 유한체를 정의하는 클래스

S256Point
- secp256k1 모델에서 사용하는 타원 곡선의 점을 정의하는 클래스
- verify
    : 서명(Signature 객체)와 메시지의 해시값(z)를 인자로 받아 해당 객체기가 공개키 P일 때의 서명이 유효한지 검증
    - r :

Signature
- secp256k1 모델에서 서명 검증에 필요한 변수 r, s를 저장하는 클래스
  i.e 서명에서 검증자에게 공개해야 할 정보
- r
    - 임의의 값이라는 의미에서 r
    - 임의의 스칼라 k에 대해서, R=kG에서 R의 x 좌표
        - k를 아는 것이 목표
    - x좌표만 알고 있다면, secp256k1의 타원 곡선 정보를 통해 y 값을 구할 수 있음
    - k를 공개하면 비밀키 e=(k-u)/v를 알 수 있기 때문에, k는 반드시 노출시키면 안된다
        - k는 이산 로그 문제인 R=kG의 해
        - R 정보는 공개해도 상관 없음
- s
    - uG + vP = kG(R)에서 (u,v)는 서명해시 값을 방정식에 담는 용도
        - (u,v) 쌍은 유일하지 않으므로, 서명자는 특정 (u,v)를 제공
          i.e s=(z+re)/k 값
        - u = z/s
        - v = r/s

PrivateKey
- 메시지에 대한 서명을 생성하기 위한 비밀키(e, P=eG)를 저장하는 클래스
    - 비밀키와 비밀키로 생성된 공개키를 저장
- sign
    : 인자로 받는 메시지 해시값(z)에 대한 서명(Signature 객체) 반환
    - 가변성 문제로 N(BASE_GROUP_ORDER)/2 보다 작은 s값만 반환
        - 유효한 서명(r,s)는 타원 곡선 위의 점
          i.e (r,s)이 유효하면, (r, N-s) 또한 유효
        - 트랜잭션 가변성
          : 네트워크상의 노드가 트랜잭션을 받고 TxID를 변경하여 조작할 수 있는 가능성
        - (r,s)<=>(r, N-s)이므로 하나로 취급해야함
- deterministic_k
    - 한번 사용한 k는 다시 사용하면 안된다
        - 재사용시 비밀키 e가 노출
        - e = (s_2*z_1 - s_1*z_2)/(r*s_1 - r*s_2)
        => 비밀키와 z를 통해 k를 유일하게 생성하는 표준안 RFC6979
    - 표준안 RFC6979을 이용하여 k를 생성하는 함수
    - 비밀키(secret)과 서명해시(z)를 이용하여 k를 생성
"""

from ecc.finite_field import FiniteFieldElement, generate_finite_field
from ecc.elliptic_curve_point import Point
from hashlib import sha256
import hmac


BASE_PRIME_NUMBER = 2 ** 256 - 2 ** 32 - 977

class S256Field(FiniteFieldElement):

    def __init__(self, num, order=None):
        super().__init__(num=num, order=BASE_PRIME_NUMBER)

    def __repr__(self):
        # 256비트로 표현되는 숫자들만 이용하기 때문에 256비트로 표현한다
        # 체의 위수는 고정되므로 표현할 필요가 없음
        return "{:x}".format(self.num).zfill(64)


BASE_ELLIPTIC_COEF = (0, 7)
BASE_GROUP_ORDER = 0xfffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141

class S256Point(Point):

    def __init__(self, x, y, a=None, b=None):
        a, b = S256Field(BASE_ELLIPTIC_COEF[0]), S256Field(BASE_ELLIPTIC_COEF[1])
        # x, y 가 정수인 경우 유한체의 원소로 변환하여 생성
        if type(x) == int:
            x = S256Field(x)
            y = S256Field(y)

        super().__init__(x,y,a,b)

    def __rmul__(self, coefficient):
        coef = coefficient %  BASE_GROUP_ORDER
        return super().__rmul__(coef)

    def __repr__(self):
        if self.x is None:
            return 'S256Point(infinity)'
        else:
            return 'S256Point({}, {})'.format(self.x, self.y)

    def verify(self, z, signature):
        """
        해당 객체가 공개키 P 일 때 인자로 들어온 서명이 올바른지 검증
        :param z: 서명해시
        :param signature: 검증하고자 하는 서명 (r,s)
        :return: boolean
        """
        # u=z/s, v=r/s를 계산하기 위한 1/s 계산
        s_inv = pow(signature.s, BASE_GROUP_ORDER-2, BASE_GROUP_ORDER)
        u = z*s_inv % BASE_GROUP_ORDER
        v = signature.r * s_inv % BASE_GROUP_ORDER

        # u*G + v*P 계산
        expected =  u*GENERATOR + v*self
        return expected.x.num == signature.r

GENERATOR = S256Point(
    0x79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798,
    0x483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8)


def example1():
    # 타원 곡선 정보
    a = 0
    b = 7

    # 유한체 정보
    p = 2 ** 256 - 2 ** 32 - 977

    # 유한군 정보
    gx = 0x79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798
    gy = 0x483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8
    n = 0xfffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141

    print("Validate generator point(i.e point is on the curve : {}".format(
        gy**2 % p == (gx**3 + a*gx + b)%p
    ))

    field = generate_finite_field(p)
    x = field(gx)
    y = field(gy)
    a = field(a)
    b = field(b)
    generotor = Point(x, y, a, b)
    print("Validate the order of group(i.e n*g == 0) : {}".format(
        n*generotor
    ))


def example2():
    print("Validate secp256k1")
    print("generator and order(i.e n*G=0) : {}".format(
        BASE_GROUP_ORDER * GENERATOR
    ))

# 서명 검증 예제
def example3():
    # 메시지 해시값
    z = 0xbc62d4b80d9e36da29c16c5d4d9f11731f36052c72401a76c23c0fb5a9b74423

    # 서명해시 요소 1 : 임의의 k에 대해서, R=kG에서 R의 x좌표
    # : 서명에서 검증자에게 제봉해야 하는 정보
    r = 0x37206a0610995c58074999cb9767b87af4c4978db68c06e8e6e81d282047a7c6

    # 서명해시 요소 2 : s=(z+re)/k 값
    # : 서명에서 검증자에게 제봉해야 하는 정보
    # u=z/s, v=r/s 로 정의됨
    s = 0x8ca63759c1157ebeaec0d03cecca119fc9a75bf8e6d0fa65c841c8e2738cdaec

    # 공개키 P의 x,y 좌표
    px = 0x04519fac3d910ca7e7138f7013706f619fa8f033e6ec6e09370ea38cee6a7574
    py = 0x82b51eab8c27c66e26c858a079bcdf4f1ada34cec420cafc7eac1a42216fb6c4

    public_point =S256Point(px, py)

    # u=z/s, v=r/s를 계산하기 위한 1/s 계산
    s_inv = pow(s, BASE_GROUP_ORDER-2, BASE_GROUP_ORDER)
    u = z*s_inv%BASE_GROUP_ORDER
    v = r*s_inv%BASE_GROUP_ORDER

    # u*G + v*P == R ?
    print("Valid Signature i.e (u*G + v*P == R) : {}".format(
        (u*GENERATOR + v*public_point).x.num == r
    ))


def exercise6():
    P = (0x887387e452b8eacc4acfde10d9aaf7f6d9a0f975aabb10d006e4da568744d06c,
                    0x61de6d95231cd89026e286df3b6ae4a894a3378e393e93a0f45b666329a0ae34)

    # signatures
    signatures = [
        (
            0xec208baa0fc1c19f708a9ca96fdeff3ac3f230bb4a7ba4aede4942ad003c0f60,
            0xac8d1c87e51d0d441be8b3dd5b05c8795b48875dffe00b7ffcfac23010d3a395,
            0x68342ceff8935ededd102dd876ffd6ba72d6a427a3edb13d26eb0781cb423c4
        ),
        (
            0x7c076ff316692a3d7eb3c3bb0f8b1488cf72e1afcd929e29307032997a838a3d,
            0xeff69ef2b1bd93a66ed5219add4fb51e11a840f404876325a1e8ffe0529a2c,
            0xc7207fee197d27c618aea621406f6bf5ef6fca38681d82b2f06fddbdce6feab6
        )
    ]

    # answer
    public_point = S256Point(P[0], P[1])

    for signature in signatures:
        z = signature[0]
        r = signature[1]
        s = signature[2]

        s_inv = pow(s, BASE_GROUP_ORDER - 2, BASE_GROUP_ORDER)
        u = z * s_inv % BASE_GROUP_ORDER
        v = r * s_inv % BASE_GROUP_ORDER

        print("Valid Signature i.e (u*G + v*P == R) : {}".format(
            (u * GENERATOR + v * public_point).x.num == r
        ))


class Signature:

    def __init__(self, r, s):
        self.r = r
        self.s = s

    def __repr__(self):
        return "Signature({:x}, {:x})".format(self.r, self.s)

# S256Point.verify 검증 - example3 예제 사용
def example4():
    P = (0x887387e452b8eacc4acfde10d9aaf7f6d9a0f975aabb10d006e4da568744d06c,
                    0x61de6d95231cd89026e286df3b6ae4a894a3378e393e93a0f45b666329a0ae34)

    # signatures
    signatures = [
        (
            0xec208baa0fc1c19f708a9ca96fdeff3ac3f230bb4a7ba4aede4942ad003c0f60,
            0xac8d1c87e51d0d441be8b3dd5b05c8795b48875dffe00b7ffcfac23010d3a395,
            0x68342ceff8935ededd102dd876ffd6ba72d6a427a3edb13d26eb0781cb423c4
        ),
        (
            0x7c076ff316692a3d7eb3c3bb0f8b1488cf72e1afcd929e29307032997a838a3d,
            0xeff69ef2b1bd93a66ed5219add4fb51e11a840f404876325a1e8ffe0529a2c,
            0xc7207fee197d27c618aea621406f6bf5ef6fca38681d82b2f06fddbdce6feab6
        )
    ]

    # answer
    public_point = S256Point(P[0], P[1])

    for signature in signatures:
        z = signature[0]
        r = signature[1]
        s = signature[2]

        sig = Signature(r,s)

        print("Valid Signature i.e (u*G + v*P == R) : {}".format(
            public_point.verify(signature=sig, z=z)
        ))


def hash256(message):
    """
    메시지의 해시값을 계산하는 함수
        - 비트코인에서는 sha256 함수를 두 번 적용
        - 해시 충돌과 같은 공격을 최소화하기 위해 두번 적용
    :param message: 메시지
    :return: 해시값
    """
    return sha256(sha256(message).digest()).digest()


# 서명 생성 예제
def example5():
    private_key = int.from_bytes(hash256(b"my secret"), "big")
    message_hash = int.from_bytes(hash256(b"my message"), "big")

    k = 1234567890
    k_inv = pow(k, BASE_GROUP_ORDER-2, BASE_GROUP_ORDER)

    r = (k * GENERATOR).x.num
    s = (message_hash + r*private_key) * k_inv % BASE_GROUP_ORDER
    public_key = private_key*GENERATOR

    print("R=eG : {}".format(public_key))
    print("z(message hash) : {}".format(hex(message_hash)))
    print("r(x of R=eG : {}".format(hex(r)))
    print("s=(z+re)/k : {}".format(hex(s)))


# k = 1234567890일때 비밀키 e와 메시지 z가 주어질 때 서명
def exercise7():
    e = 12345
    z = int.from_bytes(hash256(b"Programming Bitcoin!"), "big")

    k = 1234567890
    k_inv = pow(k, BASE_GROUP_ORDER - 2, BASE_GROUP_ORDER)

    r = (k*GENERATOR).x.num
    s = (z + r*e) * k_inv % BASE_GROUP_ORDER
    public_key = e * GENERATOR

    print("R=eG : {}".format(public_key))
    print("z(message hash) : {}".format(hex(z)))
    print("r(x of R=eG : {}".format(hex(r)))
    print("s=(z+re)/k : {}".format(hex(s)))



class PrivateKey:

    def __init__(self, secret):
        """
        메시지에 대한 서명을 생성하기 위한 비밀키(e, P=eG)를 저장하는 클래스
        - 비밀키와 비밀키로 생성된 공개키를 저장
        :param secret: int, 비밀키
        """
        self.secret = secret
        self.public_key = secret * GENERATOR

    def hex(self):
        return "{:x}".format(self.secret).zfill(64)

    def sign(self, message_hash):
        # 유한군의 order 범위 내에서 k를 랜덤생성
        k = self.deterministic_k(message_hash)
        k_inv = pow(k, BASE_GROUP_ORDER - 2, BASE_GROUP_ORDER)
        
        r = (k*GENERATOR).x.num
        s = (message_hash +  r*self.secret) * k_inv % BASE_GROUP_ORDER
        
        # N/2 보다 작은 s값만 전파
        if s > BASE_GROUP_ORDER/2:
            s = BASE_GROUP_ORDER -s
            
        return Signature(r, s)

    def deterministic_k(self, z):
        k = b'\x00' * 32
        v = b'\x01' * 32

        if z > BASE_GROUP_ORDER :
            z -= BASE_GROUP_ORDER
        z_bytes = z.to_bytes(32 ,"big")
        secrete_bytes = self.secret.to_bytes(32, "big")
        k = hmac.new(k, v + b'\x00' + secrete_bytes + z_bytes, sha256).digest()
        v = hmac.new(k, v, sha256).digest()
        k = hmac.new(k, v + b'\x01' + secrete_bytes + z_bytes, sha256).digest()
        v = hmac.new(k, v, sha256).digest()

        while True:
            v = hmac.new(k,v, sha256).digest()
            candidate = int.from_bytes(v, "big")

            if 1 <= candidate < BASE_GROUP_ORDER:
                return candidate
            k = hmac.new(k, v + b"\x00", sha256).digest()
            v = hmac.new(k, v, sha256).digest()





if __name__ == "__main__":
    print("Chapter 3-2.secp256k1 model")
    #example1()
    #example2()
    #example3()
    #exercise6()
    #example4()
    #example5()
    exercise7()