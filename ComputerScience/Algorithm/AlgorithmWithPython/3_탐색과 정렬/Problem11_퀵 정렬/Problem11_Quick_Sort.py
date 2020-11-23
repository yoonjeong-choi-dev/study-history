# Simple Quick Sort
def simple_quick_sort_min(num_list):
    """ - O(n*log(n)) where n is the length of num_list
        :param num_list: a list of integer
        :return: the sorted list
    """

    length = len(num_list)

    if length <= 1:     # 재귀 탈출 조건
        return num_list

    # 기준되는 인덱스 i.e pivot index 는 항상 마지막 인덱스
    pivot = num_list[-1]
    sub_1 = []      # pivot 보다 작은 숫자들
    sub_2 = []      # pivot 보다 큰 숫자들

    for i in range(length -1):
        if num_list[i] < pivot:
            sub_1.append(num_list[i])
        else:
            sub_2.append(num_list[i])


    return simple_quick_sort_min(sub_1) + [pivot] + simple_quick_sort_min(sub_2)




def Quick_sort_sub_min(num_list, start, end):
    """
    :param num_list: a list of integer
    :param start: a start idx to sort
    :param end: an end idx to sort
    :return: void / num_list[start~end] is sorted
    """
    if end - start <= 0:        # 재귀 탈출 조건
        return

    # 기준되는 인덱스 i.e pivot index 는 항상 마지막 인덱스
    pivot = num_list[end]
    idx = start

    for i in range(start, end):
        if num_list[i] <= pivot:
            num_list[idx], num_list[i] = num_list[i], num_list[idx]
            idx += 1

    num_list[idx], num_list[end] = num_list[end], num_list[idx]

    Quick_sort_sub_min(num_list, start, idx-1)
    Quick_sort_sub_min(num_list, idx+1, end)




def Quick_sort_min(num_list):
    """ - O(n*log(n)) where n is the length of num_list
    :param num_list: a list of integer
    :return: void / num_list is changed to the list which has been sorted
    """
    Quick_sort_sub_min(num_list, 0, len(num_list)-1)




test = [6, 8, 3, 9, 10, 1, 2, 4, 7, 5]
Quick_sort_min(test)
print(test)