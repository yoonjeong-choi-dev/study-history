import re

def find_pattern(pattern, string):
    match = re.findall(pattern, string)
    if not match:
        print("일치하는 데이터가 없습니다")
        return

    print("일치하는 데이터가 있습니다 : {}".format(match))


def simple_test_example():
    test_string = "Hello World, 1,2,3,4,5"
    find_pattern("o", test_string)
    find_pattern("[a-z]", test_string)
    find_pattern("[A-Z]", test_string)
    find_pattern("[a-zA-Z]", test_string)
    find_pattern("[0-9]", test_string)

    find_pattern(r"[\\\[\]]", r"!@#$%^&*()_+{}[]")


if __name__ == "__main__":
    simple_test_example()