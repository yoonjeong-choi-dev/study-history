"""
Load a dictionary text file as a list
- 사전 텍스트 파일을 로드하여 리스트에 저장

Arguments:
- 텍스트 파일 이름(경로)

Exceptions:
- IOError : 파일이 존재하지 않는 경우

Returns:
- 텍스트 파일의 모든 단어를 소문자로 저장한 string list

Requires-import sys
"""
import sys


def load_file(filename):
    """ 해당 파일을 연 뒤, 소문자 문자열 리스트 반환 """
    try:
        with open(filename) as file:
            # 공백을 제거하고 개행 문자를 기준으로 각 단어 분리
            loaded_text = file.read().strip().split("\n")

            # 각 단어를 소문자로 표현
            loaded_text = [x.lower() for x in loaded_text]
            return loaded_text
    except IOError as error:
        # IO 표준 에러 출력 및 중단
        print("{}\nError opening {}. Terminating program.".format(error, filename), file=sys.stderr)
        sys.exit(1)
