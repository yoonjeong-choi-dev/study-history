# Problem 1
def Find_student(std_dic, find_no):
    if find_no in std_dic:
        return std_dic[find_no]
    else:
        return '?'

test= {39: 'Justin', 14: 'John', 67: 'Mike', 105: 'Summer'}
print(Find_student(test, 105))
print(Find_student(test, 777))