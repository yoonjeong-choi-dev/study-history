# Problem 1
def Seq_search_list(num_list, num):
    """ - O(n) where n is the length of the input list num_list
    :param num_list: list of numbers
    :param num: a number to be found in num_list
    :return: list of indices of num_list i.e num=num_list[index] or empty list [] if num_list does not have num
    """
    length = len(num_list)
    idx_list = []
    for idx in range(length):
        if num == num_list[idx]:
            idx_list.append(idx)

    return idx_list




def Find_student(no_list, name_list, find_num):
    """
    :param no_list: list of student number
    :param name_list: list of student name
    :param find_num: an integer to found in no_list
    :return: student name in name_list corresponding to find_num or '?' if no_list does not contain find_num
    """
    if len(no_list)!=len(name_list):
        print(Find_student.__name__,": 1st and 2nd list have different length")
        return

    length = len(no_list)
    for i in range(length):
        if no_list[i] == find_num:
            return name_list[i]

    return '?'




stu_no = [39, 14, 67, 105]
stu_name = ['Justin', 'John', 'Mike', 'Summer']

print(Find_student(stu_no, stu_name, 67))
print(Find_student(stu_no, stu_name, 100))
