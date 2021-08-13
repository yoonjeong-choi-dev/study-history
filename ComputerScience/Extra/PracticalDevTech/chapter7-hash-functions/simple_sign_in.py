import hashlib

def computeSHA512Salted(str):
    hasher = hashlib.sha512()
    salted_str = str + "yjchoi_salted"
    hasher.update(salted_str.encode("utf-8"))
    return hasher.hexdigest()

if __name__ == "__main__":
    user_table = {}
    while True:
        user_id = input("ID를 입력하세요 :")
        passwd = input("비밀번호를 입력하세요 : ")

        if user_id in user_table:
            if user_table[user_id] == computeSHA512Salted(passwd):
                print("{}: 로그인 성공!".format(user_id))
            else:
                print("{}: 로그인 실패. 잘못된 비밀번호".format(user_id))
        else:
            user_table[user_id] = computeSHA512Salted(passwd)
            print("{}: 가입 성공!".format(user_id))