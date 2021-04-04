"""
FiniteFieldElement
- 유한체(finite field)의 원소 하나를 표현하는 클래스
- 유한체의 order는 prime number라고 가정한다
- init(num, order)
    - num : 유한체 내에서의 숫자
    - order : 유한체의 크기(소수)
- 연산(덧셈 및 곱셈)
    - 나머지 연산(MOD) 사용
    - MOD의 기준은 해당 유한체의 order
"""

class FiniteFieldElement:

    def __init__(self, num, order):
        # order 유한체에 포함되는 숫자 num인지 확인
        if num >= order or num < 0 :
            error = "num {} not in field range 0 to {}".format(num, order-1)
            raise ValueError(error)

        self.num = num
        self.order = order

    def __repr__(self):
        return "FiniteFieldElement_{}({})".format(self.order, self.num)

    def __eq__(self, other):
        if other is None:
            return False
        return self.num == other.num and self.order == self.order

    def __ne__(self, other):
        return not (self == other)

    def __add__(self, other):
        # Check that other is in the same field
        if self.order != other.order:
            raise TypeError("Cannot add tow numbers in different fields")

        num = (self.num + other.num) % self.order
        # return an instance of its class
        # self.__class__ : 상속에 대해 유연하게 대처 가능
        return self.__class__(num, self.order)

    def __sub__(self, other):
        # Check that other is in the same field
        if self.order != other.order:
            raise TypeError("Cannot add tow numbers in different fields")

        num = (self.num - other.num) % self.order
        # return an instance of its class
        # self.__class__ : 상속에 대해 유연하게 대처 가능
        return self.__class__(num, self.order)

    def __mul__(self, other):
        # Check that other is in the same field
        if self.order != other.order:
            raise TypeError("Cannot add tow numbers in different fields")

        num = (self.num * other.num) % self.order
        # return an instance of its class
        # self.__class__ : 상속에 대해 유연하게 대처 가능
        return self.__class__(num, self.order)

    def __rmul__(self, coefficient):
        ret = (self.num * coefficient) % self.order
        return self.__class__(ret, self.order)

    def __pow__(self, exponent):
        # 음수인 경우 양수 지수로 변환
        # 페르마 소정리 : a^(p-1) == 1 => a^exponent == a^(exponent + n*(p-1)) for any n
        # exponent + n*(p-1) == exponent %(p-1)
        exp = exponent % (self.order -1)    # exponent가 객체일 수 있으므로 따로 연산

        num = pow(self.num, exp, self.order)

        # return an instance of its class
        # self.__class__ : 상속에 대해 유연하게 대처 가능
        return self.__class__(num, self.order)

    def __truediv__(self, other):
        # Check that other is in the same field
        if self.order != other.order:
            raise TypeError("Cannot add tow numbers in different fields")

        # 페르마 소정리를 이용하여 역수를 구한다
        inverse = other ** (self.order -2)
        return self*inverse



# Util function for a specific field
def generate_finite_field(order):
    def finite_field(num):
        num = num % order
        return FiniteFieldElement(num, order)
    return finite_field
