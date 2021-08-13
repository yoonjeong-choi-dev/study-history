def print_text(text, encoding_type):
    byte_data = text.encode(encoding_type)
    hex_data_as_str = " ".join("{}".format(hex(c)) for c in byte_data)
    int_data_as_str = " ".join("{}".format(int(c)) for c in byte_data)

    print("====================================================================")
    print("Text : {}, Encoding Type : {}".format(text, encoding_type))
    print("전체 문자를 표현하는데 사용한 바이트 수 : {} 바이트".format(len(byte_data)))
    print("16 진수 값 : {}".format(hex_data_as_str))
    print("10 진수 값 : {}".format(int_data_as_str))
    print(type(byte_data))


if __name__ == "__main__":
    print_text("Hello", "ascii")

    print_text("Hello", "euc-kr")
    print_text("안녕하세요", "euc-kr")

    print_text("Hello", "utf-8")
    print_text("안녕하세요", "utf-8")

    print_text("Hello", "utf-16")
    print_text("안녕하세요", "utf-16")