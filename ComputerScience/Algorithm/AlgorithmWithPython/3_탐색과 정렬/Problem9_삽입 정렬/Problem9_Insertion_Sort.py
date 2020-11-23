# Easy Insertion Sort
def insertion_idx_min(num_list, num):
    """
    :param num_list: a 'sorted' list of integer
    :param num: an integer to insert in the num_list
    :return: position to insert num in the num_list
    """
    for i in range(len(num_list)):
        if num < num_list[i] :
            return i

    # 탐색 실패
    return len(num_list)


def simple_insertion_sort_min(num_list):
    """
    :param num_list: a list of integer
    :return: the sorted list // num_list is changed to []
    """
    result = []

    while num_list:
        value = num_list.pop(0)
        ins_idx = insertion_idx_min(result, value)
        result.insert(ins_idx, value)
        #print(num_list, '   ', result)

    return result

test1 = [2, 4, 5, 1, 3]


def insertion_sort_min(num_list):
    """
    :param num_list: a list of integer
    :return: void / num_list is changed to the list which has been sorted
    """
    length = len(num_list)

    for i in range(length):
        # 0 ~ i-1까지는 정렬되었다.
        # key : 삽입할 숫자
        key = num_list[i]
        # num_list[i]를 num_list[0~i-1]에 삽입
        j = i-1
        while j>=0 and num_list[j]>key:
            num_list[j+1] = num_list[j]
            j -= 1
        num_list[j+1] = key

insertion_sort_min(test1)
print(test1)