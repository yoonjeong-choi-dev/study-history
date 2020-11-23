def Bubble_sort_min(num_list):
    """ - O(n^2) where n is the length of num_list
    :param num_list: a list of integers
    :return: void / num_list is changed to the list which has been sorted
    """
    length = len(num_list)

    if length <= 0:
        return

    for idx in range(length-1):
        for i in range((length-idx)-1):
            if num_list[i] > num_list[i+1]:
                num_list[i], num_list[i+1] = num_list[i+1], num_list[i]



def Bubble_sort_max(num_list):
    """ - O(n^2) where n is the length of num_list
        :param num_list: a list of integers
        :return: void / num_list is changed to the list which has been sorted
    """
    length = len(num_list)

    if length <= 0:
        return

    for idx in range(length - 1):
        for i in range((length - idx) - 1):
            if num_list[i] < num_list[i + 1]:
                num_list[i], num_list[i + 1] = num_list[i + 1], num_list[i]



def Bubble_sort_textbook(num_list):
    """ - O(n^2) where n is the length of num_list
        :param num_list: a list of integers
        :return: void / num_list is changed to the list which has been sorted
    """
    length = len(num_list)

    while True:
        changed = False

        for i in range(length-1):
            if num_list[i] > num_list[i+1]:
                num_list[i], num_list[i + 1] = num_list[i + 1], num_list[i]
                changed = True

        if changed == False:
            return


test = [6, 8, 3, 9, 10, 1, 2, 4, 7, 5]
#Bubble_sort_min(test)
#Bubble_sort_max(test)
Bubble_sort_textbook(test)
print(test)

