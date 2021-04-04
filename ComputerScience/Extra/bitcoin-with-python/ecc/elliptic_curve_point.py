"""
Point
- 특정 타원 곡선 위의 개별 점에 대한 클래스
    - 타원 곡선의 정규식은 y^2 = x^3 + ax + b
    - a,b,x,y를 인자로 받아야 한다
    - 해당 인자는 FiniteFieldElement 객체일 수 있음
- 비트코인
    - 비트코인에서는 y^2 = x^3 + 7인 secp256k1 타원 곡선 사용
    - 비트코인에서는 개별 점들이 관심사
"""
from ecc.finite_field import FiniteFieldElement
class Point:

    def __init__(self, x, y, a, b):
        self.a = a
        self.b = b
        self.x = x
        self.y = y

        # Check the point is the point at infinity(무한 원점)
        if self.x is None and self.y is None:
            return

        # Check the point is on the curve
        if y**2 != x**3 + a*x + b:
            raise ValueError("({}, {}) is not on the curve(a={}, b={})".format(
                self.x,self.y,self.a,self.b))
    def __repr__(self):
        if self.x is None and self.y is None:
            return "Point(infinity)"
        elif isinstance(self.x, FiniteFieldElement):
            return "Point({},{})_{}_{} in FieldElement({})".format(
                self.x.num, self.y.num, self.a.num, self.b.num, self.x.order)
        else:
            return "Point({},{})_{}_{}".format(
                self.x,self.y,self.a,self.b)



    def __eq__(self, other):
        return self.x == other.x and self.y == other.y and self.a == other.a and self.b == other.b

    def __ne__(self, other):
        return not (self == other)

    def __add__(self, other):
        if self.a != other.a and self.b != other.b:
            raise TypeError("Points {}, {} are not on the same curve".format(self, other))

        # Case 1 : 무한원점은 덧셈에 대한 항등원
        # A나 B가 무한 원점인 경우 A+B는 B나 A가 된다
        if self.x is None:
            return other
        if other.x is None:
            return self

        # Case 2 : 한 점에 역원을 더하는 경우 i.e 역원을 더하는 경우
        if self.x == other.x and self.y != other.y:
            return self.__class__(None, None, self.a, self.b)

        # Case 3: x값이 다른 두점을 더하는 경우
        # Step 1 : 직선의 방정식을 이용하여 타원 곡선의 y에 대입
        # Step 2 : self, other, 직선의 교점 모두 타원 곡선 위에 있음
        # 직선의 방정식과 근과 계수와의 관계를 이용하여 계산
        # : self, other, 직선의 교점은 Step1에서 구한 방정식의 해
        if self.x != other.x:
            line_slope = (other.y - self.y)/(other.x - self.x)
            x = line_slope**2 - self.x - other.x
            y = line_slope*(self.x - x) - self.y
            return self.__class__(x, y, self.a, self.b)


        # Case 4 : 두 점이 같은 경우
        # => 접선의 기울기를 사용하여 교점을 구해 계산
        if self == other:
            # 예외 처리 : 접선의 기울기가 x축에 수직인 경우 i.e y==0 => 무한 원점 반환
            # x,y는 FiniteFieldElement이기 때문에 0과 바로 비교하지 않음
            if self.y == 0 * self.x:
                return self.__class__(None ,None, self.a, self.b)

            line_slope = (3*self.x**2 + self.a)/(2*self.y)
            x = line_slope ** 2 - self.x - other.x
            y = line_slope * (self.x - x) - self.y
            return self.__class__(x, y, self.a, self.b)

    # scalar multiple
    def __rmul__(self, coefficient):
        """
        binary expansion 기법을 이용하여 빠르게 스칼라 곱을 구현
        - coefficient를 2진법으로 표현
        - 오른쪽 비트(lsb)를 시작으로 각 비트가 1인 경우 current를 더한다
        - 비트가 왼쪽으로 한칸씩 이동할 때마다, current를 2배 해준다 (2진수니까!)
        :param coefficient:  스칼라곱에서 곱할 정수
        :return: 스칼라 곱을 통해 얻은 곡선의 점 i.e coefficient만큼 해당 점을 더하여 계산
        """
        # 비트 연산을 위한 현재 비트(lsb)와 더하는 점 current
        coef = coefficient
        current = self

        # 항등원으로 초기화
        result = self.__class__(None, None, self.a, self.b)

        while coef :
            # 비트가 1인 경우 더한다
            if coef & 1:
                result += current
            # 비트를 왼쪽으로 이동
            coef >>= 1
            current += current

        return result
