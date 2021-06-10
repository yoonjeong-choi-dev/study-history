"""
연습문제 2(Page 15) : 보급형 막대 차트
- 문자열을 인자로 받아 각 문자에 대한 막대 그래프를 출력
"""
import pprint
from collections import defaultdict

ALPHABET = 'abcdefghijklmnopqrstuvwxyz'


def print_character_chart(statement):
    """ 문자 막대 차트 출력 함수 """
    # alphabet_chart[문자] : 해당 문자에 대한 리스트
    alphabet_chart = defaultdict(list)

    # 문장 순회
    for char in statement:
        lower_case = char.lower()
        if lower_case in ALPHABET:
            alphabet_chart[lower_case].append(lower_case)

    # 차트 출력
    pprint.pprint(alphabet_chart, width=110)


def etaoin_chart():
    """ 프로젝트 메인 함수 """
    # 만족하는 이름이 나올 때까지 반복
    while True:
        # 프로그램 도입부
        statement = input("Enter a statement : ")

        # 함수 호출
        print_character_chart(statement)

        # 만족하는지 입력
        try_again = input("Try again? (Press Enter else q to quit) : ")
        if try_again.lower() == "q":
            break


if __name__ == "__main__":
    etaoin_chart()
