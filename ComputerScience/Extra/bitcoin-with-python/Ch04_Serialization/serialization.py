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

from ecc.finite_field import FiniteFieldElement
from ecc.elliptic_curve_point import Point
import hashlib
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



def hash256(message):
    """
    메시지의 해시값을 계산하는 함수
        - 비트코인에서는 sha256 함수를 두 번 적용
        - 해시 충돌과 같은 공격을 최소화하기 위해 두번 적용
    :param message: 메시지
    :return: 해시값
    """
    return sha256(sha256(message).digest()).digest()


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



def exercise1():
    secrets = [5000, 2018**5, 0xdeadbeef123456]
    answers = [
        "04ffe558e388852f0120e46af2d1b370f85854a8eb0841811ece0e3e03d282d57c315dc72890a4f10a1481c031b03b351b0dc79901ca18a00cf009dbdb157a1d10",
        "04027f3da1918455e03c46f659266a1bb5204e959db7364d2f473bdf8f0a13cc9dff87647fd023c13b4a4994f17691895806e1b40b57f4fd22581a4f46851f3b06",
        "04d90cd625ee87dd38656dd95cf79f65f60f7273b67d3096e68bd81e4f5342691f842efa762fd59961d0e99803c61edba8b3e3f7dc3a341836f97733aebf987121"
    ]
    for idx, secret in enumerate(secrets):
        private_key = PrivateKey(secret)
        noncompressed = private_key.public_key.sec(False).hex()
        print("{} -> {} :  {}".format(secret, noncompressed, noncompressed==answers[idx]))

def exercise2():
    secrets = [5001, 2019**5, 0xdeadbeef54321]
    answers = [
        "0357a4f368868a8a6d572991e484e664810ff14c05c0fa023275251151fe0e53d1",
        "02933ec2d2b111b92737ec12f1c5d20f3233a0ad21cd8b36d0bca7a0cfa5cb8701",
        "0296be5b1292f6c856b3c5654e886fc13511462059089cdf9c479623bfcbe77690"
    ]
    for idx, secret in enumerate(secrets):
        private_key = PrivateKey(secret)
        noncompressed = private_key.public_key.sec(True).hex()
        print("{} -> {} :  {}".format(secret, noncompressed, noncompressed==answers[idx]))

def exercise3():
    r = 0x37206a0610995c58074999cb9767b87af4c4978db68c06e8e6e81d282047a7c6
    s = 0x8ca63759c1157ebeaec0d03cecca119fc9a75bf8e6d0fa65c841c8e2738cdaec
    answer = "3045022037206a0610995c58074999cb9767b87af4c4978db68c06e8e6e81d282047a7c60221008ca63759c1157ebeaec0d03cecca119fc9a75bf8e6d0fa65c841c8e2738cdaec"

    signature = Signature(r,s)

    der = signature.der()
    print("signature serialization - {} : {}".format(
        der, der.hex()==answer
    ))


BASE58_ALPHABET = '123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz'

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

def exercise4():
    hexs = [
        "7c076ff316692a3d7eb3c3bb0f8b1488cf72e1afcd929e29307032997a838a3d",
        "eff69ef2b1bd93a66ed5219add4fb51e11a840f404876325a1e8ffe0529a2c",
        "c7207fee197d27c618aea621406f6bf5ef6fca38681d82b2f06fddbdce6feab6"
    ]

    answers = [
        "9MA8fRQrT4u8Zj8ZRd6MAiiyaxb2Y1CMpvVkHQu5hVM6",
        "4fE3H2E6XMp4SsxtwinF7w9a34ooUrwWe4WsW1458Pd",
        "EQJsjkd6JaGwxrjEhfeqPenqHwrBmPQZjJGNSCHBkcF7"
    ]

    for idx, h in enumerate(hexs):
        hex_to_bytes = bytes.fromhex(h)
        encoded = encode_base58(hex_to_bytes)
        print("Base58 encoded {} :{}".format(
            encoded, encoded== answers[idx]
        ))

def encode_base58_checksum(bytes_string):
    """
    특정 바이트와 체크섬(해당 바이트의 hash256 값에서 4비트를 취하여 연결한뒤 Base58로 인코딩
    - 시작 바이트(주소 종류) 및 SEC 형식 주소를 합친 결과와 해당 결과의 체크섬을 합쳐서 Base58로 인코딩
    :param bytes_string: 시작 바이트(주소 종류) 및 SEC 형식 주소를 합친 결과 str
    :return: Base58로 인코딩된 str(체크섬이 포함)
    """
    return encode_base58(bytes_string + hash256(bytes_string)[:4])

def hash160(sec_message):
    """
    hash160기반으로 메시지의 해시값을 계산하는 함수
    - 비트코인 주소 형식 생성 프로세스의 2단계에 해당
    - SEC 형식의 주소를 sha256과 ripemd160 해시를 연속으로 사용
    :param sec_message: 해시할 SEC 형식 메시지
    :return: 해시값
    """
    return hashlib.new("ripemd160", sha256(sec_message).digest()).digest()

def exercise5():
    # (비밀 키, 압축 여부, 테스트넷 여부)
    information = [
        (5002, False, True),
        (2020**5, True, True),
        (0x12345deadbeef, True, False)
    ]

    answers = [
        "mmTPbXQFxboEtNRkwfh6K51jvdtHLxGeMA",
        "mopVkxp8UhXqRYbCYJsbeE1h1fiF64jcoH",
        "1F1Pn2y6pDb68E5nYJJeba4TLg2U7B6KF1"
    ]

    for idx, info in enumerate(information):
        secret_key = info[0]
        is_compressed = info[1]
        is_test_net = info[2]

        private_key = PrivateKey(secret_key)
        public_key = private_key.public_key

        address = public_key.address(is_compressed, is_test_net)
        print("Bitcoin addres {} : {}".format(
            address, address == answers[idx]
        ))

def exercise6():
    # (비밀 키, 압축 여부, 테스트넷 여부)
    information = [
        (5003, True, True),
        (2021 ** 5, False, True),
        (0x54321deadbeef, True, False)
    ]

    answers = [
        "cMahea7zqjxrtgAbB7LSGbcQUr1uX1ojuat9jZodMN8rFTv2sfUK",
        "91avARGdfge8E4tZfYLoxeJ5sGBdNJQH4kvjpWAxgzczjbCwxic",
        "KwDiBf89QgGbjEhKnhXJuH7LrciVrZi3qYjgiuQJv1h8Ytr2S53a"
    ]

    for idx, info in enumerate(information):
        secret_key = info[0]
        is_compressed = info[1]
        is_test_net = info[2]

        private_key = PrivateKey(secret_key)
        wif = private_key.wif(is_compressed, is_test_net)
        print("Bitcoin addres {} : {}".format(
            wif, wif == answers[idx]
        ))

# exercise7 : 리틀엔디언을 읽어 정수로 변환하는 함수
def little_endian_to_int(bytes_str):
    return int.from_bytes(bytes_str, 'little')

# exercise8 : 정수를 리틀엔디언으로 변환하는 함수
def int_to_little_endian(num, length):
    return num.to_bytes(length, "little")

# 커스텀 비밀키를 통한 테스트넷 주소 만들기
def exercise9():
    my_message = b'jimmy@programmingblockchain.com my secret'
    answer = "mft9LRNtaBNtpkknB8xgm17UvPedZ4ecYL"

    secret_key = little_endian_to_int(hash256(my_message))
    private_key = PrivateKey(secret_key)
    address = private_key.public_key.address(testnet=True)
    print("TestNet address {} : {}".format(
        address, address == answer
    ))



if __name__ == "__main__":
    print("Chapter 4. Serialization")
    #exercise1()
    #exercise2()
    #exercise3()
    #exercise4()
    #exercise5()
    #exercise6()
    exercise9()