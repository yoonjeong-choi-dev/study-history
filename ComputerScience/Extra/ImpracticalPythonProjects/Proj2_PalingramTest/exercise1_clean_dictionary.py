"""
연습문제 1(Page 33) : 사전 정리
사전 데이터 변경
- 사전 데이터 리스트에 특정 데이터를 추가
- 특정 알파벳을 추가
"""


def modify_dictionary_data(permissbile_set, dictionary_list):
    """
    :param permissbile_set: 추가할 알파벳 세트
    :param dictionary_list: 조작할 사전 데이터 리스트
    :return: 변경된 사전 데이터 리스트
    """
    modified = []
    for word in dictionary_list:
        # 길이가 2이상인 단어면 추가
        if len(word) > 1:
            modified.append(word)
        # 추가할 알파벳인 경우 추가
        elif len(word) == 1 and word in permissbile_set:
            modified.append(word)
        else:
            continue

    return modified


def main():
    """ 검증 """
    word_list = ['a', 'nurses', 'i', 'stack', 'b', 'c', 'cat']
    permissible = {'a', 'i'}

    result = modify_dictionary_data(permissible, word_list)
    print("{}".format(result))


if __name__ == "__main__":
    main()
