# 입력값의 최댓값 찾기

def max_num(num_list):
    """ - O(n) where n is the length of the input list(num_list)
    :param num_list: a list of integers
    :return:  maximum number of the input list
    """
    maximum = num_list[0]
    for num in num_list:
        if maximum < num:
            maximum=num
    return maximum


def max_idx(num_list):
    """ - O(n) where n is the length of the input list(num_list)
    :param num_list: a list of integers
    :return:  index of the maximum number in the input list
    """
    length = len(num_list)
    max_index = 0
    for idx in range(1, length):
        if num_list[max_index] < num_list[idx]:
            max_index = idx

    return max_index



test = [17, 92, 18, 33, 58, 7, 33, 42]
print(max_num(test))
print(max_idx(test))