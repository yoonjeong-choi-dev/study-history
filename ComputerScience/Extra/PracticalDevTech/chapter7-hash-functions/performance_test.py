from hashes import computeMD5, computeSHA512
import time

hash_generate = 1000000

md5_start = time.monotonic()
for i in range(hash_generate):
    computeMD5(str("hash_test_key_{}".format(i)))
md5_end = time.monotonic()

sha512_start = time.monotonic()
for i in range(hash_generate):
    computeSHA512(str("hash_test_key_{}".format(i)))
sha512_end = time.monotonic()

print("MD5 time : {}".format(md5_end - md5_start))
print("SHA512 time : {}".format(sha512_end - sha512_start))