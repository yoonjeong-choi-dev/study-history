def Seq_search(num_list, num):
    """ - O(n) where n is the length of the input list num_list
    :param num_list: list of numbers
    :param num: a number to be found in num_list
    :return: index of num_list i.e num=num_list[index] or -1 if num_list does not have num
    """
    length = len(num_list)

    for idx in range(length):
        if num == num_list[idx]:
            return idx

    return -1

v = [17, 92, 18, 33, 58, 7, 33, 42]

print(Seq_search(v, 18))
print(Seq_search(v, 33))
print(Seq_search(v, 900))
