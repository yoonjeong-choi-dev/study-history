"""
아나그램 만들기
- 사용자가 입력한 문장으로 아나그램 문자열 생성
    - 구성하는 각 단어는 사전에 있는 단어
"""
from collections import Counter
import Proj2_PalingramTest.load_dictionary as load_dictionary


class AnagramCreator:
    process_separator_string = "\n********************************************\n" \
                               "******************************************** "
    """ 사전 파일을 이용한 아나그램 생성기 """
    def __init__(self, dictionary_file="2of4brif.txt"):
        """ 아나그램 생성을 위한 사전 데이터 및 이름 초기화 """
        # 검색한 사전 데이터 로드
        self.dict_file = load_dictionary.load_file(dictionary_file)
        self.dict_file.append("a")
        self.dict_file.append("i")
        self.dict_file = sorted(self.dict_file)

        self.init_name = ""

    def set_name_for_anangram(self):
        """ 프로세스 초기화 : 아나그램을 생성하기 위한 이름 입력 """
        self.init_name = input("Enter a name : ")

    @staticmethod
    def find_anagrams(name, word_list):
        """
        현재 이름에서 만들 수 있는 아나그램 생성 및 출력
        :param name: 아나그램 생성을 위한 이름 문자열
        :param word_list: 아나그램이 실제 단어인지 확인하기 위한 사전 단어 리스트
        :return: None
        """
        # 각 문자의 빈도수 저장
        name_letter_map = Counter(name)
        anagrams = []

        # 사전의 각 단어가 아나그램 구성 단어의 후보
        for word in word_list:
            test = ""
            word_letter_map = Counter(word.lower())
            # 해당 단어는 name의 부분 문자열을 구성해야 아나그램 후보
            for letter in word:
                if word_letter_map[letter] <= name_letter_map[letter]:
                    test += letter

            # name에 대한 필터링 결과 test가 현재 word와 일치하는 경우에만 아나그램
            if Counter(test) == word_letter_map:
                anagrams.append(word)

        # 가능한 아나그램 단어 출력
        print("===========Anagrams===========")
        print(*anagrams, sep="\n")
        print()
        print("Remaining leters = {}".format(name))
        print("Number of remaining letters = {}".format(len(name)))
        print("Number of remaining (real word) anagrams = {}".format(len(anagrams)))
        print("======================")

    def process_choice(self, name):
        """ 사용자가 선택하는 단어를 받아 name(남아있는 글자의 문자열)에서의 아나그램 생성
            - 아나그램 후보가 아닌 단어도 부분 문자열인 경우 생성 가능
        """

        # 반복 프로세스
        while True:
            choice = input("\nMake a choice(word: your chioce, enter : start, # : end) : ")
            if choice == "":
                self.main_process()
            elif choice == "#":
                return None, None

            # 사용자 입력 값을 아나그램 후보로 저장
            candidate = "".join(choice.lower().split())

            left_over_list = list(name)
            is_valid_choice = True
            for letter in candidate:
                if letter in left_over_list:
                    left_over_list.remove(letter)
                else:
                    is_valid_choice = False
                    break

            if is_valid_choice:
                break
            else:
                print("Won't work!. Make Another choic!")

        name = "".join(left_over_list)
        return choice, name

    def main_process(self):
        """ 메인 프로세스 """
        # 아나그램 생성에 사용하는 이름 pre-processing
        name = "".join(self.init_name.lower().split())
        name = name.replace("-", "")

        # 반복해서 아나그램 이름 생성 프로세스를 진행하기 위한 변수들
        limit = len(name)
        phrase = ""
        is_running = True

        # name의 모든 문자를 사용할 때까지 in_running은 참값
        while is_running:
            temp_phrase = phrase.replace(" ", "")

            # 미완성 상태 => 아나그램 생성 계속 진행
            if len(temp_phrase) < limit:
                print("Length of anagram phase = {}".format(len(temp_phrase)))

                # 현재 이름에 대한 아나그램 생성
                AnagramCreator.find_anagrams(name, self.dict_file)
                print("Cuurent anagram phrase={}".format(phrase))

                # 아나그램에 사용할 단어 입력
                choice, name = self.process_choice(name)
                if choice is None:
                    return
                phrase += choice + " "
            # 완성 상태 => 또다른 아나그램 생성 or 끝
            elif len(temp_phrase) == limit:
                print("\n*******FINISHED!!!*******\n")
                print("Anagram of name = {}\n".format(phrase))

                try_again = input("\nTry Again for another anagram? (Press 'n' or 'q' to quit) : ")
                if try_again == "n" or try_again == "q":
                    is_running = False
                else:
                    self.main_process()

    def main(self):
        """ 사용자 입력에 대해서 아나그램 메인프로세스 진행 """
        while True:
            print(AnagramCreator.process_separator_string)
            self.set_name_for_anangram()
            self.main_process()
            print(AnagramCreator.process_separator_string)

            try_again = input("\nCreate for another name (Press 'n' or 'q' to quit) : ")
            if try_again == "n" or try_again == "q":
                break


if __name__ == "__main__":
    creator = AnagramCreator("2of4brif.txt")
    creator.main()
