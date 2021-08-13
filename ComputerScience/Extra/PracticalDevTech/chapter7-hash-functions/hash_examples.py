from hashes import *


def hash_test(str1, str2, hasher, header):
    print(header)
    print("{}={} / 길이={}".format(str1, hasher(str1), len(hasher(str1))))
    print("{}={} / 길이={}".format(str2, hasher(str2), len(hasher(str2))))
    print()


if __name__ == "__main__":
    str1 = "해시 값 1"
    str2 = "해시 값 2"

    hash_test(str1, str2, computeMD5, "MD5 Test")
    hash_test(str1, str2, computeSHA1, "SHA1 Test")
    hash_test(str1, str2, computeSHA256, "SHA256 Test")
    hash_test(str1, str2, computeSHA512, "SHA512 Test")