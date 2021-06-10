"""
팔린그램 주문 찾기
- Goal
  - 파일 로드
  - cProfile을 이용하여 코드 성능 향상
- 문장 자체가 회문(palindrome)인 팔린그램(palingram) 문장 찾기
  - 외부 파일(사전 텍스트 파일)을 로드하여 이를 이용하여 두 단어로 구성된 문장 생성
  - 해당 문장이 팔린그램인지 확인

< Solution >
1. 핵심 단어
- 두 단어로 이루어진 문장이 팔린그램인 경우 하나의 단어가 핵심 단어
  - 핵심 단어는 [역전단어][회문] 이나 [회문][역전단어] 형태로 구성
  - 두 단어는 [역전단어][회문] [역전단어`] 이거나, [역전단어`] [회문][역전단어] 형태
2. 팔린그램 찾기
- 각 단어가 핵심 단어인지 확인
- 단어를 [역전단어][회문] 이나 [회문][역전단어] 형태로 쪼갠다
  - i.e 단어를 두 개의 sub string으로 쪼갠다
    => word[i:], word[i:word_len-1]
  - 역전 단어부분을 반전시킨 것이 사전에 있는지 확인
  - 회문 부분은 회문인지 확인
"""
import load_dictionary


def find_palingram(word, word_list):
    """
    :param word: 핵심 단어 후보가 되는 단어 
    :param word_list: 팔린그램을 만들기 위한 단어 리스트
    :return: word가 핵심 단어인 팔린그램 리스트. 없으면 빈 리스트
    """
    word_len = len(word)
    if word_len <= 1:
        return []

    palingram_list = []

    # 역전 단어의 역전 및 회문 검사를 빠르게 하기 위해 미리 역전시킨다
    word_reversed = word[::-1]
    for i in range(word_len):
        # word : [회문][역전단어] 형태
        if word[i:] == word_reversed[:word_len-i] and word_reversed[word_len-i:] in word_list:
            palingram_list.append((word, word_reversed[word_len-i:]))

        # word : [역전단어][회문] 형태
        if word[:i] == word_reversed[word_len-i:] and word_reversed[:word_len-i] in word_list:
            palingram_list.append((word_reversed[:word_len-i], word))

    return palingram_list


def find_palingram_improved(word, word_set):
    """
    Set 자료 구조를 이용하여 "in" 연산자 속도 향상
    :param word: 핵심 단어 후보가 되는 단어 
    :param word_set: 팔린그램을 만들기 위한 단어 Set
    :return: word가 핵심 단어인 팔린그램 리스트. 없으면 빈 리스트
    """
    word_len = len(word)
    if word_len <= 1:
        return []

    palingram_list = []

    # 역전 단어의 역전 및 회문 검사를 빠르게 하기 위해 미리 역전시킨다
    word_reversed = word[::-1]
    for i in range(word_len):
        # word : [회문][역전단어] 형태
        if word[i:] == word_reversed[:word_len-i] and word_reversed[word_len-i:] in word_set:
            palingram_list.append((word, word_reversed[word_len-i:]))

        # word : [역전단어][회문] 형태
        if word[:i] == word_reversed[word_len-i:] and word_reversed[:word_len-i] in word_set:
            palingram_list.append((word_reversed[:word_len-i], word))

    return palingram_list


def find_palingram_in_dictionary():
    """ 성능 테스트를 위해 메인 코드 분리 """
    word_list = load_dictionary.load_file("2of4brif.txt")
    palingram_list = []

    for word in word_list:
        palingrams_wrt_word = find_palingram(word, word_list)
        palingram_list = palingram_list + palingrams_wrt_word

    return palingram_list


def find_palingram_in_dictionary_improved():
    """ 성능 테스트를 위해 메인 코드 분리 """
    word_list = load_dictionary.load_file("2of4brif.txt")
    word_set = set(word_list)
    palingram_list = []

    for word in word_list:
        palingrams_wrt_word = find_palingram_improved(word, word_set)
        palingram_list = palingram_list + palingrams_wrt_word

    return palingram_list


def main():
    """ 메인 프로젝트 """
    # palingram_list = find_palingram_in_dictionary()
    palingram_list = find_palingram_in_dictionary_improved()

    # 찾은 팔린그램을 알파벳 순으로 정렬하여 출력
    sorted_list = sorted(palingram_list)

    print("\nNumber of palingrams = {}\n".format(len(sorted_list)))
    for first, second in sorted_list:
        print("{} {}".format(first, second))


if __name__ == "__main__":
    main()
