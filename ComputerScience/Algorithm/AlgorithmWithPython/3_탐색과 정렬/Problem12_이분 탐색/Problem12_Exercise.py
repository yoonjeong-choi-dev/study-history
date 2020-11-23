def Binary_search_recursive(num_list, target, start = 0, end = 0):
    """ - O(log(n)) where n is the length of num_list
    :param num_list: a 'sorted' list of integer
    :param target: an integer to search in the num_list
    :param start: start index of num_list to search
    :param end: end index of num_list to search
    :return: idx s.t target==num_list[idx] or -1 if num_list has no target
    """

    if start > end:
        return -1

    mid = (start + end)//2

    if target == num_list[mid]:
        return mid
    elif target < num_list[mid]:
        return Binary_search_recursive(num_list, target, 0, mid-1)
    else:
        return Binary_search_recursive(num_list, target, mid+1, end)






test = [1, 4, 9, 16, 25, 36, 49, 64, 81]
print(Binary_search_recursive(test, 36, 0, len(test)-1))
print(Binary_search_recursive(test, 11, 0 ,len(test)-1))