# Problem 1
# Simple Merge Sort
def simple_merge_sort_max(num_list):
    """
    :param num_list: list of integers
    :return: the sorted list // num_list is changed to []
    """
    length = len(num_list)
    if length <= 1:             # 재귀 탈출 조건
        return num_list

    # 2개로 분할 후 merge sort
    mid = length//2
    group1 = simple_merge_sort_max(num_list[:mid])
    group2 = simple_merge_sort_max(num_list[mid:])

    # 분할한 groups 을 병합
    # group1&2 : 이미 정렬되어 있는 리스트
    # group1 과 group2의 가장 작은 값을 비교하여 result 에 정렬한다.
    result = []

    # group1 이나 group2 가 모두 사라질때 까지
    while group1 and group2:
        if group1[0] < group2[0]:
            result.append(group1.pop(0))
        else :
            result.append(group2.pop(0))

    # group1 이나 group2 중 남아 있는 리스트 정렬
    while group1:
        result.append(group1.pop(0))
    while group2:
        result.append(group2.pop(0))

    return result




def Merge_sort_max(num_list):
    """ - O(n*log(n)) where n is the length of num_list
    :param num_list: a list of integer
    :return: void / num_list is changed to the list which has been sorted
    """
    length = len(num_list)

    if length <=1:               # 재귀 탈출 조건
        return

    # 2개로 분할 후 merge sort
    mid = length//2
    sub_1 = num_list[:mid]
    sub_2 = num_list[mid:]
    # 분할한 groups 을 Merge Sort
    Merge_sort_max(sub_1)
    Merge_sort_max(sub_2)

    # 분할한 groups 을 병합
    idx_1 = 0
    idx_2 = 0
    idx_sort = 0

    # group1 이나 group2 가 모두 사라질때 까지 num_list 를 업데이트
    while idx_1 < len(sub_1) and idx_2 < len(sub_2):
        if sub_1[idx_1] < sub_2[idx_2]:
            num_list[idx_sort] = sub_1[idx_1]
            idx_1 += 1
            idx_sort += 1
        else:
            num_list[idx_sort] = sub_2[idx_2]
            idx_2 += 1
            idx_sort += 1

    # group1 이나 group2 중 남아 있는 리스트 정렬
    while idx_1 <len(sub_1):
        num_list[idx_sort] = sub_1[idx_1]
        idx_1 += 1
        idx_sort += 1

    while idx_2 < len(sub_2):
        num_list[idx_sort] = sub_2[idx_2]
        idx_2 += 1
        idx_sort += 1




test = [6, 8, 3, 9, 10, 1, 2, 4, 7, 5]
Merge_sort_max(test)
print(test)







