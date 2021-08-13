import re

"""
비밀번호 검증
- 최소 8글자
- 대문자 최소 1개 
- 소문자 최소 1개
- 숫자 최소 1개
- 특수문자 최소 1개
"""

def check_password(password):
    # 최소 8글자
    if len(password) < 8:
        print("최소 8글자여야 합니다")
        return False

    # 최소 소문자 1개
    at_least_small_pattern = r"[a-z]+"
    result = re.search(at_least_small_pattern, password)
    if not result:
        print("소문자가 적어도 1개 있어야 합니다")
        return False

    # 최소 대문자 1개
    at_least_capital_pattern = r"[A-Z]+"
    result = re.search(at_least_capital_pattern, password)
    if not result:
        print("대문자가 적어도 1개 있어야 합니다")
        return False

    # 최소 숫자 1개
    at_least_digit_pattern = r"[0-9]+"
    result = re.search(at_least_digit_pattern, password)
    if not result:
        print("숫자가 적어도 1개 있어야 합니다")
        return False

    # 최소 특수문자 1개
    at_least_special_pattern = r"[@#$%^&+=]"
    result = re.search(at_least_special_pattern, password)
    if not result:
        print("특수문자(@#$%^&+=)가 적어도 1개 있어야 합니다")
        return False

    print("비밀번호 검증 성공!")
    return True


if __name__ == "__main__":
    test_cases = [
        "candy",
        "candy9320",
        "Candy9320",
        "candy9320@",
        "CANDY9320@",
        "Candy9320&"
    ]

    for test in test_cases:
        check_password(test)