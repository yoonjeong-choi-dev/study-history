def find_same_name(name_list):
    """ O(n) where n is the length of name_list
    :param name_list: a list of names
    :return: a set of names repeated in the name_list
    """
    name_dict = {}

    # name_list 에 있는 이름들의 갯수 저장
    for name in name_list:
        if name in name_dict:
            name_dict[name] += 1
        else:
            name_dict[name] = 1

    name_set = set()
    for name in name_dict:
        if name_dict[name] != 1:
            name_set.add(name)


    return name_set


test1 = ['Tom', 'Jerry', 'Mike', 'Tom']
test2 = ['Tom', 'Jerry', 'Mike', 'Tom', 'Mike']

print(find_same_name(test1))
print(find_same_name(test2))

