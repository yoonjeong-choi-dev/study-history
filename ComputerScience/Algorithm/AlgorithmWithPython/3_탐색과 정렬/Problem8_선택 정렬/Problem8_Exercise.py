# Problem 2
# Simple Selection Sort
def max_idx(num_list):
    """ - O(n) where n is the length of the input list(num_list)
    :param num_list: a list of integers
    :return: idx for minimum number of the input list
    """
    length = len(num_list)
    if length == 0:
        print(max_idx.__name__, ': wrong input')
        return

    idx = 0
    for i in range(length):
        if num_list[idx] < num_list[i]:
            idx = i

    return idx



def simple_selection_sort_max(num_list):
    """ - O(n^2) where n is the length of the input list(num_list)
    :param num_list: a list of integers
    :return: the list which has been sorted // num_list is changed to []
    """
    if len(num_list)==0:
        print(simple_selection_sort_max.__name__, ': wrong input')
        return

    result = []
    while num_list:
        idx = max_idx(num_list)
        value = num_list.pop(idx)
        result.append(value)

    return result


test_1 = [2, 4, 5, 1, 3]



def Selection_sort_max(num_list):
    """ - O(n^2) where n is the length of the input list(num_list)
    :param num_list: a list of integers
    :return: void / num_list is changed to the list which has been sorted
    """

    length = len(num_list)

    if length==0:
        print(Selection_sort_max.__name__, ': wrong input')
        return

    for i in range(length-1):
        idx = i
        for j in range(i+1, length):
            if num_list[j] > num_list[idx]:
                idx = j

        num_list[i], num_list[idx] = num_list[idx], num_list[i]



Selection_sort_max(test_1)
print(test_1)
