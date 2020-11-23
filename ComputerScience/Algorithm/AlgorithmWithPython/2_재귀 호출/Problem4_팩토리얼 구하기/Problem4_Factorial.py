def factorial_repeat(num):
    """
        - O(num)
    :param num: non-negative integer
    :return: 1 * 2 * ... * num
    """
    if num == 0:
        return 1

    pro = 1
    for i in range(1,num+1):
        pro *= i

    return pro



def factorial_recursive(num):
    """
        - O(num)
    :param num: non-negative integer
    :return: 1 * 2 * ... * num
    """

    if num==0:
        return 1
    # 재귀 탈출 조건 :
    if num==1:
        return 1

    return num*factorial_recursive(num-1)


num1 = 1; num2 = 5 ;num3 = 10


print(factorial_recursive(num1))
print(factorial_recursive(num2))
print(factorial_recursive(num3))