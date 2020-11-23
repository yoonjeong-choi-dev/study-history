def Binary_search(num_list, target):
    """ - O(log(n)) where n is the length of num_list
    :param num_list: a 'sorted' list of integer
    :param target: an integer to search in the num_list
    :return: idx s.t target==num_list[idx] or -1 if num_list has no target
    """
    start = 0
    end = len(num_list) - 1

    while start<=end:
        mid = (start + end)//2
        if target == num_list[mid]:
            return mid
        elif target < num_list[mid]:
            end = mid - 1
        else :
            start = mid + 1

    # 탐색 실패
    return -1



test = [1, 4, 9, 16, 25, 36, 49, 64, 81]
print(Binary_search(test, 36))
print(Binary_search(test, 11))