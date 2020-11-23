# Problem 1

def min_num(num_list):
    """ - O(n) where n is the length of the input list(num_list)
    :param num_list: a list of integers
    :return:  minimum number of the input list
    """
    minimum = num_list[0]
    for num in num_list:
        if minimum > num:
            minimum=num
    return minimum

max_num = int(input("입력할 정수의 갯수 : "))
number_list = []
for i in range(max_num):
    a = int(input("정수 입력 : "))
    number_list.append(a)

print(min_num(number_list))