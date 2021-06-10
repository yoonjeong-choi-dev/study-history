"""
도전 프로젝트 1(Page 34) : 재귀적 접근
- 재귀 함수를 이용한 회문 찾기
"""
import load_dictionary


def is_palindrome(word, cur_idx=0):
    """
    재귀적으로 회문 판단
    :param word: 회문 판단 단어
    :param cur_idx: 현재 인덱스
    :return: 회문 여부
    """
    word_len = len(word)

    # 단어의 길이가 1 이상인 경우만 테스트
    if word_len < 2:
        return False

    # 단어의 절반까지 판단한 경우 => 회문
    if cur_idx >= word_len/2:
        return True

    # 현재 인덱스에 대해서 회문 조건 불만족인 경우
    if word[cur_idx] != word[word_len-1-cur_idx]:
        return False
    else:
        return is_palindrome(word, cur_idx+1)


def validate():
    """ 알고리즘 검증 : 기작성된 find_palindrome 이용 """
    import find_palindromes
    word_list = load_dictionary.load_file("2of4brif.txt")

    for word in word_list:
        if find_palindromes.is_palindrome(word) != is_palindrome(word):
            print("Wrong")

    print("Correct")


def find_palindromes():
    """
    사전 파일에서 회문을 모두 찾아 출력
    """
    word_list = load_dictionary.load_file("2of4brif.txt")
    palindrome_list = []

    for word in word_list:
        if is_palindrome(word):
            palindrome_list.append(word)

    print("\nNumber of palindromes found = {}\n".format(len(palindrome_list)))
    print(*palindrome_list, sep="\n")


if __name__ == "__main__":
    validate()
