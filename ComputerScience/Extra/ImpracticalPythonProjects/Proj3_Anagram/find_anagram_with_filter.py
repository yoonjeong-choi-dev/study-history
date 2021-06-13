"""만
아나그램 만들기 Imporved
- 사전에 없지만, 그럴싸한 단어 생성을 위한 조합 생성
    - 기본적으로 permutation을 통해 무작위 문자열 생성
    - 다음의 3개의 필터를 사용하여 그럴싸한 단어들을 필터링
        - c-v 맵
        - 트라이그램
        - 다이어그램
- c-v 맵
    - 각 단어에 대해 자음은 c, 모음은 v로 치환
    - 치환된 c-v맵을 통해 발생 빈도가 낮은 c-v맵을 가진 단어는 후보에서 제외
    - 사전 데이터를 이용하여, 발생 빈도수 계산
    - 여러 후보 단어 중, 특정 발생 빈도 수 이하인 c-v맵을 가진 단어들은 제외시킨다
- 트라이그램
    - 세 개의 연이은 글자들을 포함하는 세 개의 문자로 구성된 집합
    - 흔하게 발생하지 않는 트라이그램은 제외
- 다이어그램
    - 두 개의 글자로 구성된 문자 쌍
    - 흔하게 발생하지 않는 다이어그램은 제외
"""
from itertools import permutations
from collections import Counter
import Proj2_PalingramTest.load_dictionary as load_dictionary

VOWELS = 'aeiouy'


def main():
    # 이름 입력
    name = input("Enter a word :")
    if name == "":
        name = "tmvoordle"
    name = name.lower()

    target_name = input("Enter a target name :")
    if target_name == "":
        target_name = "voldemort"

    # 필터링 설정
    word_list = load_dictionary.load_file("2of4brif.txt")
    trigram_filter = load_dictionary.load_file("least-likely_trigrams.txt")
    rejects = ['dt', 'lr', 'md', 'ml', 'mr', 'mt', 'mv',
               'td', 'tv', 'vd', 'vl', 'vm', 'vr', 'vt']
    first_pair_rejects = ['ld', 'lm', 'lt', 'lv', 'rd',
                          'rl', 'rm', 'rt', 'rv', 'tl', 'tm']

    # 필터링 진행
    pre_procceesed = same_length_words(name, word_list)
    cv_map_filter = create_cv_map_filter(pre_procceesed)
    filtered = filter_cv_map(name, cv_map_filter)
    filtered = filter_trigram(filtered, trigram_filter)
    filtered = filter_diagram(filtered, rejects, first_pair_rejects)
    find_target_after_filtering(target_name, filtered)


def same_length_words(name, word_list, verbose=True):
    """ name과 동일한 길이를 가진 아나그램 후보 생성 """
    # 길이가 같은 후보
    len_name = len(name)
    same_length_list = [word.lower() for word in word_list if len(word) == len_name]

    if verbose:
        print("Initial words in word list : {}".format(len(word_list)))
        print("Same length words in word list : {}".format(len(same_length_list)))

    return same_length_list


def cv_mapper(word):
    """ word에 대한 c-v 맵 생성 """
    temp = ""
    for letter in word:
        if letter in VOWELS:
            temp += "v"
        else:
            temp += "c"

    return temp


def create_cv_map_filter(word_list, dropped=0.05, verbose=True):
    """
    c-v 맵으로 변환된 단어 리스트에서 빈도수가 높은 c-v맵들만 반환
    :param word_list: 필터링에 사용할 표본 단어 리스트
    :param dropped: 필터링 비율
    :param verbose: 필터링 결과 출력 여부
    :return: 필터링된 사용 가능한 c-v map 셋
    """

    # 단어 리스트의 단어들을 c-v 맵으로 변환
    cv_mapped_words = []
    for word in word_list:
        cv_mapped_words.append(cv_mapper(word))

    # c-v맵에서 빈도수가 낮은 특정 맵들 제거
    total_cv_maps = len(set(cv_mapped_words))
    num_removed = int(total_cv_maps*dropped)
    most_cv_mapped_dict = Counter(cv_mapped_words).most_common(total_cv_maps-num_removed)

    # 제거되고 남은 c-v맵 리스트
    filterd_map_list = set()
    for pattern, _ in most_cv_mapped_dict:
        filterd_map_list.add(pattern)

    if verbose:
        print("Length of filetered cv maps : {}".format(len(filterd_map_list)))

    return filterd_map_list


def filter_cv_map(name, cv_map_filter, verbose=True):
    """ cv_map_filter 없는 c-v 맵을 가진 단어는 제외 """
    permutated_names = {"".join(i) for i in permutations(name)}

    filtered = set()
    for candidate in permutated_names:
        if cv_mapper(candidate) in cv_map_filter:
            filtered.add(candidate)

    if verbose:
        print("Length of initial permutations : {}".format(len(permutated_names)))
        print("Length after cv map filter : {}".format(len(filtered)))

    return filtered


def filter_trigram(filtered_names, trigram_filter, verbose=True):
    """ trigram_filter에 있는 단어 제외 """
    words_to_filtered = set()

    # filtered_names에 대해 필터링
    for candidate in filtered_names:
        for trigram in trigram_filter:
            trigram = trigram.lower()
            if trigram in candidate:
                words_to_filtered.add(candidate)

    filtered = filtered_names - words_to_filtered

    if verbose:
        print("Length after trigram filter : {}".format(len(filtered)))

    return filtered


def filter_diagram(filtered_names, diagram_filter, starting_diagram_filter, verbose=True):
    """
    diagram_filter과 starting_diagram_filter에 있는 단어 제외
    :param filtered_names: 필터링할 이름들
    :param diagram_filter: 필터링에 사용할 다이어그램 리스트
    :param starting_diagram_filter: 시작 부분에 필터링을 사용할 다이어그램 리스트
    :param verbose: 필터링 결과 출력 여부
    :return: 필터링 결과
    """
    words_to_filtered = set()

    for candidate in filtered_names:
        for diagram in diagram_filter:
            if diagram in candidate:
                words_to_filtered.add(candidate)
        for diagram in starting_diagram_filter:
            if candidate.startswith(diagram):
                words_to_filtered.add(candidate)

    filtered = filtered_names - words_to_filtered

    if verbose:
        print("Length after diagram filter : {}".format(len(filtered)))

    return filtered


def find_target_after_filtering(target_name, filtered_names):
    """ 원하는 이름을 발견하였는지 출력 """
    if target_name in filtered_names:
        print("{} found!".format(target_name))
    else:
        print("{} NOT found...".format(target_name))


if __name__ == "__main__":
    main()
