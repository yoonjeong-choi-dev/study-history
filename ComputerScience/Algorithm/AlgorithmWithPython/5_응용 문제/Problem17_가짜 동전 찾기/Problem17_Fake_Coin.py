"""
Problem : 겉보기에 똑같은 n 개의 동전 중에 한개는 무게가 가벼운 가짜 동전이다.
          여기에는 좌우 무게를 비교할 수 있는 양팔 저울이 있다.
          가짜 동전을 찾는 함수를 구현하라.
"""

# Set coins
import random
num_coin = 100
fake = int(random.random()*num_coin)




# Way 1
def find_fake_sequential(coins=0, fake_coin=0):
    " Complexity : O(n)"
    def sub_fake_seq(left1, left2, right1, right2):
        if left1<= fake_coin <= left2 :
            return -1
        elif right1<= fake_coin <= right2:
            return 1

        return 0

    for i in range(1, coins - 1):
        result = sub_fake_seq(0, 0, i, i)
        if result ==- 1:
            return 0
        elif result == 1:
            return i

    return -1





# Way 2
def sub_fake_bi(left1, left2, right1, right2):
    if left1<= fake <= left2 :
        return -1
    elif right1<= fake <= right2:
        return 1


def find_fake_binary(left, right):
    " Complexity : O(log(n))"
    # 동전이 하나남았으면 그 동전이 가짜 동전
    if left == right:
        return -1

    # 동전 수가 홀수면 두 그룹으로 나누고 마지막 한개를 남긴다
    mid = (right - left +1)//2
    sub1_left = left
    sub1_right = left + mid - 1
    sub2_left = left + mid
    sub2_right = sub2_left + mid -1

    # 두 그룹을 sub_fake_bi를 이용하여 저울질 한다
    result = sub_fake_bi(sub1_left, sub1_right, sub2_left, sub2_right)

    # 왼쪽이 가벼운 경우
    if result == -1:
        return find_fake_binary(sub1_left, sub1_right)
    elif result == 1:
        return find_fake_binary(sub2_left, sub2_right)
    else:
        return right






print("real fake coin :", fake)
print(find_fake_binary(0, num_coin-1))