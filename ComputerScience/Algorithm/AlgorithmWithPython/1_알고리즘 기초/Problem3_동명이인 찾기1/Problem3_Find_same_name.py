"""
Problem : For a given list, make a set of elements which are repeated
"""

def Find_same_name(name_list):
    """
        - O(n^2) : n is the length of name_list
    :param name_list: a list to find repeated element
    :return: a set of repeated element
    """
    length = len(name_list)
    name_set = set()

    for i in range(length-1):       # 마지막 원소는 비교대상이 없다
        test_name = name_list[i]
        if test_name in name_set:
            continue

        for j in range(i+1,length):
            if test_name == name_list[j]:
                name_set.add(test_name)

    return name_set

name1 = ['Tom', 'Jerry', 'Mike', 'Tom']
name2 = ['Tom', 'Jerry', 'Mike', 'Tom', 'Mike']
print(Find_same_name(name1))
print(Find_same_name(name2))

