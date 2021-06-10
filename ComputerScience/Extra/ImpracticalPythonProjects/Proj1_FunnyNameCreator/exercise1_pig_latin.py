"""
연습문제 1(Page 15) : 피그라틴
입력받은 단어의 첫 문자가 자음인지 모음인지에 따라 새로운 단어 생성
- 모음인 경우 : 어미에 way 추가
- 자음인 경우 : 자음을 끝으로 이동 후, 어미에 ay 추가
"""

# 모음
VOWELS = ["a", "e", "i", "o", "u"]


def pig_latin():
    """ 프로젝트 메인 함수 """
    # 만족하는 이름이 나올 때까지 반복
    while True:
        # 프로그램 도입부
        word = input("Enter a word : ")

        # 모음인 경우 : 어미에 way 추가
        if word[0] in VOWELS:
            word = word + "way"
        # 자음인 경우 : 자음을 끝으로 이동 후, 어미에 ay 추가
        else:
            word = word[1:] + word[0] + "ay"

        # 결과 출력
        print("Pig latin : {}\n".format(word))

        # 만족하는지 입력
        try_again = input("Try again? (Press Enter else q to quit) : ")
        if try_again.lower() == "q":
            break


if __name__ == "__main__":
    pig_latin()
