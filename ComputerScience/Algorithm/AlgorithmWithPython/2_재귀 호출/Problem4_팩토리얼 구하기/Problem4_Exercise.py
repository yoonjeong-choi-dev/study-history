# Problem 1
def sum_recursive(num):
    if num <= 0:
        print(sum_recursive.__name__,': wrong input ')
        return

    if num == 1:
        return 1

    return num + sum_recursive(num-1)



# Problem 2
def find_max_recursive(num_list):
    length = len(num_list)
    if length == 0:
        print(find_max_recursive.__name__, ': wrong input')

    if length ==1:
        return num_list[0]

    max_num = find_max_recursive(num_list[1:length])
    if num_list[0] > max_num:
        return num_list[0]
    else:
        return max_num

n_list = [1,4,88,23,15,12,9,10]
print(find_max_recursive(n_list))
