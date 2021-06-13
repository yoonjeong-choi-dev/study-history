"""
단일어 아나그램 찾기
- 외부 파일(사전 텍스트 파일)을 로드하여 두 단어가 서로 아나그램 관계 인지 확인
    - 로드 모듈은 Project2의 load_dictionary 사용
- 두 문자열이 서로 아나그램이 되는지 검사
"""

import Proj2_PalingramTest.load_dictionary as load_dictionary


def is_anagram(word1, word2):
    """
    :param word1: str
    :param word2: str
    :return: 두 단어가 서로 아나그램인지 여부
    """
    # 각 단어를 소문자로 바꾸어 알파벳순으로 정렬
    word1_sorted = sorted(word1.lower())
    word2_sorted = sorted(word2.lower())

    return word1_sorted == word2_sorted


def find_angaram_in_dictionary(word_test, word_list):
    """
    :param word_test: 아나그램 테스트 단어 
    :param word_list: 테스트 단어 세트
    :return: 아나그램인 단어 리스트
    """
    anagram_list = []

    for word in word_list:
        # 자기 자신은 아나그램으로 취급하지 않는다
        if word_test == word:
            continue
        if is_anagram(word, word_test):
            anagram_list.append(word)

    return anagram_list


def main():
    """ 아나그램 테스트 메인 """
    word_list = load_dictionary.load_file("2of4brif.txt")

    name = "Foster"
    print("Input name : {}\nUsing name : {}".format(name, name.lower()))

    result = find_angaram_in_dictionary(name, word_list)
    if len(result) == 0:
        print("You need a larger dictionary or a new name")
    else:
        print("Anagrams=", *result, sep="\n")


if __name__ == "__main__":
    main()
