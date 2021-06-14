"""
연습문제 1(Page 61) : 다이어그램 찾기
- tmvoordle에 대한 모든 아나그램의 다이어그램들 찾기
- 각 다이어그램의 사전 출현 빈도수 출력
"""
from itertools import permutations
from re import finditer
from collections import defaultdict
import Proj2_PalingramTest.load_dictionary as load_dictionary


# 문제 설정
name = "tmvoordle"
len_name = len(name)
word_list = load_dictionary.load_file("2of4brif.txt")

# 아나그램 및 다이어그램 생성
digrams = set()
permutated_names = {"".join(i) for i in permutations(name)}
for permutated in permutated_names:
    # 다이어그램 생성
    for i in range(len_name-1):
        digrams.add(permutated[i]+permutated[i+1])

# 사전에서의 빈도 수 체크
frequency_dict = defaultdict(int)
for word in word_list:
    word_lower = word.lower()
    for digram in digrams:
        # digram이 word_lower에서 발견되는 빈도 수 확인
        for _ in finditer(digram, word_lower):
            frequency_dict[digram] += 1

print("digram frequency count: ")
for digram, count in frequency_dict.items():
    print("{} : {}".format(digram, count))
