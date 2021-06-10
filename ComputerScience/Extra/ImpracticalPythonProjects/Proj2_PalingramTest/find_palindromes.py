"""
회문 찾기

Method 1 :
- 단어를 역방향으로 반전시킨 후 단어 비교
- 문자열의 슬라이싱 사용 : word[::-1]
"""
import load_dictionary


def is_palindrome(word):
    """
    Method 1 을 사용하여 회문 여부 확인
    :param word: 단어
    :return: 회문 여부
    """
    # 단어의 길이가 1 이상인 경우만 테스트
    if len(word) < 2:
        return False

    return word == word[::-1]


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
    find_palindromes()
