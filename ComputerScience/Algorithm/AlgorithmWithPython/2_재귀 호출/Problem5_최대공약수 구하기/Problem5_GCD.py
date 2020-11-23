def gcd(num1, num2):
    min_num = abs(min(num1, num2))
    while True:
        if num1%min_num==0 and num2%min_num==0:
            return min_num

        min_num -= 1


def gcd_Euclid(num1, num2):
    """
    :param num1: integer
    :param num2: integer
    :return: gcd(greatest common divisor

    Euclid algorithm :
        1. gcd(a,b)=gcd(b,a%b)
        2. gcd(b,0)=b
    """
    if num2 == 0:
        return num1
    return gcd_Euclid(num2, num1%num2)

print(gcd_Euclid(8, 36))