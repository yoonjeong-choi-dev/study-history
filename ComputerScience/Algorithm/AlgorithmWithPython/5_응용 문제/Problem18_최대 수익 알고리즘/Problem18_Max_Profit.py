""" < 최대 수익 알고리즘 >
Problem : 어떤 주식이 특정 기간 동안의 주가가 주어졌을 때, 그 주식 한 주를 한번 사고 팔아 얻을 수 있는 최대 수익을 계산해라.
          단, 아직 사지 않은 주식은 팔 수 없으므로, 단순하게 최대값에서 최솟값을 빼면 안된다.

Solution :
    1. 모든 경우를 비교하기  - 사는 날 기준
    2. 모든 경우를 비교하기  - 파는 날 기준
"""

import time
import random

def max_profit_1(stock_list):
    " - O(n^2) where n==day"

    if len(stock_list)<=1:
        print("stock_list is too short(<=1)!")
        return

    day = len(stock_list)
    max_pro = stock_list[1] - stock_list[0]

    for buy in range(day-1):
        for sell in range(buy+1, day):
            profit = stock_list[sell]-stock_list[buy]
            if max_pro < profit:
                max_pro = profit

    return max_pro




def max_profit_2(stock_list):
    " - O(n) where n==day"

    if len(stock_list) <= 1:
        print("stock_list is too short(<=1)!")
        return
    day_len = len(stock_list)
    max_pro = stock_list[day_len-1] - stock_list[0]
    min_price = stock_list[0]

    for day in range(1, day_len):
        profit = stock_list[day] - min_price

        # 최대 수익 업데이트
        if profit > max_pro:
            max_pro = profit

        # 최솟값 업데이트
        if stock_list[day] < min_price:
            min_price = stock_list[day]

    return max_pro











stock_ex = [10300, 9600, 9800, 8200, 7800, 8300, 9500, 9800, 10200, 9500]
print("Way 1 :", max_profit_1(stock_ex))
print("Way 2 :", max_profit_2(stock_ex))