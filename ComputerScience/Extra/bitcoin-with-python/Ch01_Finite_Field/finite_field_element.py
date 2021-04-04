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

    # Exercise1
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

    # Exercise3
    def __sub__(self, other):
        # Check that other is in the same field
        if self.order != other.order:
            raise TypeError("Cannot add tow numbers in different fields")

        num = (self.num - other.num) % self.order
        # return an instance of its class
        # self.__class__ : 상속에 대해 유연하게 대처 가능
        return self.__class__(num, self.order)

    # Exercise6
    def __mul__(self, other):
        # Check that other is in the same field
        if self.order != other.order:
            raise TypeError("Cannot add tow numbers in different fields")

        num = (self.num * other.num) % self.order
        # return an instance of its class
        # self.__class__ : 상속에 대해 유연하게 대처 가능
        return self.__class__(num, self.order)

    def __pow__(self, exponent):
        # 음수인 경우 양수 지수로 변환
        # 페르마 소정리 : a^(p-1) == 1 => a^exponent == a^(exponent + n*(p-1)) for any n
        # exponent + n*(p-1) == exponent %(p-1)
        exponent = exponent % (self.order -1)

        num = pow(self.num, exponent, self.order)

        # return an instance of its class
        # self.__class__ : 상속에 대해 유연하게 대처 가능
        return self.__class__(num, self.order)

    # Exercise9
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


def example1():
    a = FiniteFieldElement(7, 13)
    b = FiniteFieldElement(6, 13)
    print(a)
    print(b)
    print(a==b)
    print(a==a)

def exercise2():
    finite57 = generate_finite_field(57)

    print(finite57(44) + finite57(33))
    print(finite57(9) - finite57(29))
    print(finite57(17) + finite57(42) + finite57(49))
    print(finite57(52) - finite57(30) - finite57(38))

def exercise4():
    finite97 = generate_finite_field(97)
    print(finite97(95)*finite97(45)*finite97(31))
    print(finite97(17)*finite97(13)*finite97(19)*finite97(44))
    print((finite97(12)**7)*(finite97(77)**49))

def exercise5():
    finite19 = generate_finite_field(19)

    k_list = [1, 3, 7, 13, 18]
    k_elements = [finite19(i) for i in k_list]
    all_elements = [finite19(i) for i in range(19)]

    for k in k_elements:
        print("{} generates ....".format(k.num))
        gen_list = []
        for i in all_elements:
            ret = (k*i).num
            gen_list.append(ret)
            print(ret, end=" ")

        ordered = set(gen_list)
        print("\norders : {}".format(ordered))

# 페르마의 소정리
def exercise7():
    primes = [7, 11, 17, 31]

    for prime in primes:
        finite_field = generate_finite_field(prime)
        finite_field_elements = [finite_field(i) for i in range(1, prime)]
        results = []

        for element in finite_field_elements:
            result_element = element**(prime-1)
            results.append(result_element.num)

        print("{} generates {}".format(prime, set(results)))

def exercise8():
    finite31 = generate_finite_field(31)
    print(finite31(3)/finite31(24))
    print(finite31(17)**(-3))
    print(finite31(4)**(-4)*finite31(11))


if __name__ == "__main__":
    #example1()
    #exercise2()
    #exercise4()
    #exercise5()
    #exercise7()
    exercise8()