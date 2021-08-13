import random
import os
import time

# 각 난수를 100만번 생성
num_generation = 1000000

# Test 1 : 유사 난수
random.seed()
pseudo_start = time.monotonic()
for i in range(num_generation):
    random.random()
pseudo_end = time.monotonic()

# Test 2 : 안전한 난수
secure_start = time.monotonic()
for i in range(num_generation):
    os.urandom(4)
secure_end = time.monotonic()

print("Pseudo Random : {}".format(pseudo_end - pseudo_start))
print("Secure Random : {}".format(secure_end - secure_start))