# sum from 1 ~ n(= input)
def sum_up(num):
    """ By usual iteration : O(num
    :param num: integer to be sum from 1
    :return: summation from 1 to 'num'
    """
    sum = 0
    for i in range(1, num+1):
        sum += i

    return sum

def sum_Gauss(num):
    """ By Gauss formulation - n(n + 1)/2   : O(1)
    :param num: integer to be sum from 1
    :return: summation from 1 to 'num'
    """
    return num*(num +1)//2


print(sum_up(100))
print(sum_Gauss(100000000))