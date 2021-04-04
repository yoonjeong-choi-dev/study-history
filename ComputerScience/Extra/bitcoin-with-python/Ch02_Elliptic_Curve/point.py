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
            return "Point at infinity on the curve(a={}, b={})".format(self.a, self.b)
        else:
            return "Point ({}, {}) on the curve(a={}, b={})".format(
                self.x, self.y, self.a, self.b)

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y and self.a == other.a and self.b == other.b

    # Exercise2
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

        # Case 2(Exercise3) : 한 점에 역원을 더하는 경우 i.e 역원을 더하는 경우
        if self.x == other.x and self.y != other.y:
            return self.__class__(None, None, self.a, self.b)

        # Case 3(Exercise5) : x값이 다른 두점을 더하는 경우
        # Step 1 : 직선의 방정식을 이용하여 타원 곡선의 y에 대입
        # Step 2 : self, other, 직선의 교점 모두 타원 곡선 위에 있음
        # 직선의 방정식과 근과 계수와의 관계를 이용하여 계산
        # : self, other, 직선의 교점은 Step1에서 구한 방정식의 해
        if self.x != other.x:
            line_slope = (other.y - self.y)/(other.x - self.x)
            x = line_slope**2 - self.x - other.x
            y = line_slope*(self.x - x) - self.y
            return self.__class__(x, y, self.a, self.b)


        # Case 4(Exercise7) : 두 점이 같은 경우
        # => 접선의 기울기를 사용하여 교점을 구해 계산
        if self == other:
            # 예외 처리 : 접선의 기울기가 x축에 수직인 경우 i.e y==0 => 무한 원점 반환
            # x,y는 FiniteFieldElement이기 때문에 0과 바로 비교하지 않음
            if self.y == 0*self.x:
                return self.__class__(None ,None, self.a, self.b)

            line_slope = (3*self.x**2 + self.a)/(2*self.y)
            x = line_slope ** 2 - self.x - other.x
            y = line_slope * (self.x - x) - self.y
            return self.__class__(x, y, self.a, self.b)


def exercise1():
    curve = (5, 7)
    point_list = [(2,4), (-1,-1), (18, 77), (5,7)]

    for point in point_list:
        try:
            Point(*point, *curve)
            print("({}, {}) is on the curve".format(point[0], point[1]))
        except ValueError as e:
            print(e)

def exercise4():
    curve = (5,7)
    p1 = Point(2, 5,*curve)
    p2 = Point(-1, -1, *curve)
    print(p1+p2)

def exercise6():
    curve = (5, 7)
    p1 = Point(-1, -1, *curve)
    p2 = Point(-1, -1, *curve)
    print(p1 + p2)



if __name__ == "__main__":
    print("Chapter 2 : Elliptic Curve")
    #exercise1()
    #exercise4()
    exercise6()