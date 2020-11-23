# Problem 1
def Show_partner(name_list):
    length = len(name_list)
    for name in range(length-1):
        for partner in range(name+1, length):
            print(name_list[name], '-', name_list[partner])

test_name1 = ['Tom', 'Jerry', 'Mike', 'James']
Show_partner(test_name1)