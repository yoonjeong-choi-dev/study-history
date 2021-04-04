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

"""
직렬화
- 클래스의 객체들을 저장하거나 네트워크로 전송하는 방법
    - 직렬화 : 스트림을 통해 데이터를 읽을 수 있도록 객체 데이터를 연속적인 데이터로 변환하는 과정
    - 역직렬화 : 직렬화된 연속적인 데이터를 다시 객체 형태로 변환하는 과정
- 네트워크 사용 비용과 영구 저장매체에 보관하는 비용을 최소화 하기위해 클래스의 크기를 최소하는 것이 바람직
- 직렬화/역직렬화 기능을 추가해야 하는 클래스
    - S256Point : SEC
    - Signature : DER
    - PrivateKey : WIF
        - 비밀키는 일반적으로는 직렬화 필요 X
        - 비밀키는 네트워크로 전파하지 않는 "비밀" 정보
        - 한 지갑에서 다른 지갑으로 옮기고 싶은 경우 필요

S256Point 직렬화 : SEC(Standards for Efficient Cryptography)
- ECDSA(Elliptic Curve Digital Signature Algorithm) 공개키를 직렬화하는 표준안
- S256Point.sec() 메서드를 통해 구현
    - 공개키는 S256Point 객체
- S256Point.parse(sec)
    - 직렬화된 공개키를 역직렬화하여 (x,y)점을 가지는 S256Point 객체를 반환하는 클래스 메서드
- 두 가지 직렬화방식
    - 비압축식
    - 압축식
- 비압축식
    - 접두부 : 1바이트의 0x04
    - x,y 좌표 : 32바이트 빅엔디언 정수
    - 빅엔디언
      : 숫자를 왼쪽에서 오른쪽으로 읽는 방식
- 압축식
    - 같은 x 좌표값을 가지는 타원곡선 위의 점은 2개 (y^2 = x^3 + 7)
        - (x,y)가 타원곡선의 점이면, (x, p-y) 또한 타원곡선의 점
        - 비트코인에서 사용하는 타원곡선은 이미 정해져 있음
          => x좌표만 알고 있으면, y좌표 2개를 계산 가능
        - 소수 p는 홀수이기 때문에, (y, p-y)는 (홀,짝) or (짝, 홀)
          => y에 대한 정보는 홀/짝만 알려주어도 된다
    - 접두부 : 1바이트의 0x03(y가 홀수) or 0x02(y가 짝수)
    - x좌표 : 32바이트 빅엔디언 정수
    => 33바이트로 표현 가능
- 압축식에서 y좌표를 구하는 방법
    - S256Field.sqrt()를 통해 구현
    - 주어진 v에 대해서 w^2=v 를 만족하는 w를 구하는 문제
    - 페르마 소정리에 의해 w^(p-1)=1
      => w^2=w^2 * 1=w^2 * w^(p-1)=w^(p+1)
      => w = w^((p+1)/2) where p+1 : even
      => w = w^((p+1)/2) = (w^2)^((p+1)/4) = v^((p+1)/4)
    - w = v^((p+1)/4)
    - secp256k1에서 사용하는 소수 p는 p%4=3이기 때문에 (p+1)/4는 나누어 떨어진다


Signature 직렬화 1 - DER(Distinguished Encoding Rules)
- DER은 서명을 직렬화하는 표준
    - 비트코인이 막 출범했을 때 사용한 방식
- Signature는 S256Point처럼 압축 불가능
    - S256Point는 x값을 통해 y값을 유도 가능
    - Signature는 s값을 통해 r값 유도 불가능
- DER 서명 형식 구성
    1. 0x30 바이트로 시작
    2. 서명의 길이
        : 보통 0x44 or 0x45
    3. r값의 시작을 표시하는 0x02
    4. r값을 빅엔디언 정수로 표현
        - 첫번째 바이트가 0x80이상이면, 앞에 00을 붙인다
    5. s값의 시작을 표시하는 0x02
    6. s값을 빅엔디언 정수로 표현
        - 첫번째 바이트가 0x80이상이면, 앞에 00을 붙인다
- SEC와 다르게 r과 s 값은 32바이트로 표현하지 않고, 실제 수에 해당하는 바이트로만 표현
-  첫번째 바이트가 0x80이상이면, 앞에 00을 붙이는 이유
    - DER 형식은 음수값도 수용가능한 일반 형식
      => 첫번째 바이트가 0x80이상이면 음수를 의미
         첫비트가 1이면 음수를 의미함
    - ECDSA 서명에서는 모든 숫자가 양수
      => 첫번째 바이트가 0x80이상이면, 앞에 00을 붙여 양수로 만든다
    - r과 s는 최대 256비트로 표현
        - 최대 32바이트로 표현
        - r과 s값을 직렬화하기위해서는 첫바이트가 0x80이상이면, 최대 33바이트가 필요

Signature 직렬화 2 : Base58 부호화
- Review : DER
    - 비트코인이 막 출범했을 때 사용한 방식
    - 여러 이유로 이 방식은 미사용 트랜잭션 출력(UTXO, Unspent transaction output)을 방만하게 저장하여 보안성 이슈 존재
- 직렬화 고려 사항
    - 공개키의 가독성
    - 공개키 길이
    - 보안성
- 6비트를 이용하여 1개의 숫자로 표현
    - 0/O, 1/I 를 제외한 아라비아 숫자와 알파벳 대소문자를 사용
    - 총 10+26+26-4=58개의 글자를 6비트짜리 하나의 숫자로 표현
    - 맨 마지막에 체크섬을 붙여 실수 탐지 기능 추가


S256Point 직렬화 - 비트코인 주소 형식 : ripemd160
- Review : SEC
    - 압축 SEC 방식의 264비트(33바이트)도 여전히 비트 수가 많음
    - 보안에 취약(6장 스크립트)
- 주소의 길이를 줄이고 보안성을 높인 ripemd160
- 비트코인 생성 방법
    1. 시작 주소
        - 메인넷 주소 : 0x00
        - 테스트넷 주소 : 0x6f
            - 비트코인 소프트웨어 개발에 활용되는 비트코인 네트워크
    2. hash160 방법으로 주소를 해시
        - SEC 형식 주소를 sha256에 넣고, 다시 ripemd160 해시에 넣어 결과 추출하는 방식
        - 연속으로 2개의 해시함수를 사용
    3. 1과 2의 결과를 합친다
    4. 3의 결과를 다시 sha256으로 해시하여 첫 4바이트만 추출
        - 해당 4바이트는 체크섬
    5. 3의 결과와 4의 결과를 합쳐 Base58 부호화

PublicKey 직렬화 - WIF(Wallet Import Format)
- 비밀키를 읽기 쉽도록 직렬화하는 방법
    - Base58 부호화를 사용
- WIF 직렬화 방법
    1. 시작 주소
        - 메인넷 주소 : 0x80
        - 테스트넷 주소 : 0xef
    2. 비밀키는 32바이트 길이의 빅엔디언으로 표현
    3. 대응하는 공개키(P=eG)를 압축 SEC 형식으로 표현했다면 2번 결과에 0x01 추가
    4. 1,2,3을 순서대로 연결
    5. 4번 결과에 대해 hash256 방식으로 해시
    6. 5번 결과에서 첫 4바이트를 체크섬으로 취함
    7. 5,6을 순서대로 연결하여 Base56 부호화
"""

from io import BytesIO
from ecc.finite_field import FiniteFieldElement
from ecc.elliptic_curve_point import Point
from ecc.utils import encode_base58_checksum, hash160
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

    def sqrt(self):
        return self**((BASE_PRIME_NUMBER+1)//4)


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

    def sec(self, compreesed=True):
        """
        :param compreesed: 압축식 직렬화인지 나타내는 boolean
        :return: SEC 압축을 통한 바이너리 문자열
        """
        if compreesed:
            if self.y.num % 2 ==0:
                return b"\x02" + self.x.num.to_bytes(32, "big")
            else:
                return b"\x03" + self.x.num.to_bytes(32, "big")
        else:
            return b"\x04" + self.x.num.to_bytes(32, "big") + self.y.num.to_bytes(32, "big")

    @classmethod
    def parse(cls, sec_binary):
        # 비압축식인 경우
        if sec_binary[0] == 4:
            x = int.from_bytes(sec_binary[1:33], "big")
            y = int.from_bytes(sec_binary[33:65], "big")
            return S256Point(x, y)

        # 압축식인 경우
        is_even = (sec_binary[0]==2)
        x = S256Field(int.from_bytes(sec_binary[1:33], "big"))

        # y 계산 : sqrt(x**3 - 7)
        y_2pow = x**3 + S256Field(BASE_ELLIPTIC_COEF[1])
        y = y_2pow.sqrt()

        if y.num % 2 == 0:
            even_y = y
            odd_y = S256Field(BASE_PRIME_NUMBER - y.num)
        else:
            even_y = S256Field(BASE_PRIME_NUMBER - y.num)
            odd_y = y

        return S256Point(x, even_y) if is_even else S256Point(x, odd_y)

    def hash160(self, compressed=True):
        """
        공개키인 객체에 대해서 hash160을 적용한 해시값 계산
        - 비트코인 주소 생성 2단계에 해당
        :param compressed: SEC 압축 여부
        :return: 해시값
        """
        return hash160(self.sec(compressed))

    def address(self, compressed=True, testnet=False):
        """
        공개키인 객체에 대해서 비트코인 주소 생성
        :param compressed: SEC 압축 여부
        :param testnet: 테스트넷 여부
        :return: 비트코인 주소
        """
        h160 = self.hash160(compressed)

        # 테스트넷의 경우
        if testnet:
            prefix = b"\x6f"
        # 메인넷의 경우
        else:
            prefix = b"\x00"

        return encode_base58_checksum(prefix+h160)


GENERATOR = S256Point(
    0x79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798,
    0x483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8)

class Signature:

    def __init__(self, r, s):
        self.r = r
        self.s = s

    def __repr__(self):
        return "Signature({:x}, {:x})".format(self.r, self.s)

    def der(self):
        # r을 빅엔디언 정수로 표현 : 최대 32 바이트
        r_binary = self.r.to_bytes(32, byteorder="big")

        # r_binary에서 필요없는 바이트 제거
        # why? : SEC와 다르게 r과 s 값은 32바이트로 표현하지 않고, 실제 수에 해당하는 바이트로만 표현
        r_binary = r_binary.lstrip(b"\x00")

        # 첫번째 바이트가 0x80이상이면, 앞에 00을 붙인다
        if r_binary[0] & 0x80:
            r_binary = b"\x00" + r_binary

        # r값의 시작을 표시하는 0x02 추가
        r_binary = bytes([2, len(r_binary)]) + r_binary

        # s을 빅엔디언 정수로 표현 : 최대 32 바이트
        s_binary = self.s.to_bytes(32, byteorder="big")

        # s_binary에서 필요없는 바이트 제거
        # why? : SEC와 다르게 r과 s 값은 32바이트로 표현하지 않고, 실제 수에 해당하는 바이트로만 표현
        s_binary = s_binary.lstrip(b"\x00")

        # 첫번째 바이트가 0x80이상이면, 앞에 00을 붙인다
        if s_binary[0] & 0x80:
            s_binary = b"\x00" + s_binary

        # s값의 시작을 표시하는 0x02 추가
        s_binary = bytes([2, len(s_binary)]) + s_binary

        # 서명(s,r)추가
        result = r_binary + s_binary

        # 시작 바이트 0x30 및 서명 길이 추가
        result = bytes([0x30, len(result)]) +result
        return result

    @classmethod
    def parse(cls, signature_bin):
        s = BytesIO(signature_bin)
        compound = s.read(1)[0]
        if compound != 0x30:
            raise SyntaxError("Bad Signature")
        length = s.read(1)[0]
        if length + 2 != len(signature_bin):
            raise SyntaxError("Bad Signature Length")
        marker = s.read(1)[0]
        if marker != 0x02:
            raise SyntaxError("Bad Signature")
        rlength = s.read(1)[0]
        r = int.from_bytes(s.read(rlength), 'big')
        marker = s.read(1)[0]
        if marker != 0x02:
            raise SyntaxError("Bad Signature")
        slength = s.read(1)[0]
        s = int.from_bytes(s.read(slength), 'big')
        if len(signature_bin) != 6 + rlength + slength:
            raise SyntaxError("Signature too long")
        return cls(r, s)


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

        r = (k * GENERATOR).x.num
        s = (message_hash + r * self.secret) * k_inv % BASE_GROUP_ORDER

        # N/2 보다 작은 s값만 전파
        if s > BASE_GROUP_ORDER / 2:
            s = BASE_GROUP_ORDER - s

        return Signature(r, s)

    def deterministic_k(self, z):
        k = b'\x00' * 32
        v = b'\x01' * 32

        if z > BASE_GROUP_ORDER:
            z -= BASE_GROUP_ORDER
        z_bytes = z.to_bytes(32, "big")
        secrete_bytes = self.secret.to_bytes(32, "big")
        k = hmac.new(k, v + b'\x00' + secrete_bytes + z_bytes, sha256).digest()
        v = hmac.new(k, v, sha256).digest()
        k = hmac.new(k, v + b'\x01' + secrete_bytes + z_bytes, sha256).digest()
        v = hmac.new(k, v, sha256).digest()

        while True:
            v = hmac.new(k, v, sha256).digest()
            candidate = int.from_bytes(v, "big")

            if 1 <= candidate < BASE_GROUP_ORDER:
                return candidate
            k = hmac.new(k, v + b"\x00", sha256).digest()
            v = hmac.new(k, v, sha256).digest()

    def wif(self, public_compressed=True, testnet=False):
        # 비밀키를 32바이트 빅엔디언으로 표현
        secret_bytes = self.secret.to_bytes(32, "big")

        # 테스트넷의 경우
        if testnet:
            prefix = b"\xef"
        # 메인넷의 경우
        else:
            prefix = b"\x80"

        # 공개키 압축 여부에 대한 추가 바이트 설정
        if public_compressed:
            compressed_bytes = b"\x01"
        else:
            compressed_bytes = b""

        return encode_base58_checksum(prefix + secret_bytes + compressed_bytes)


