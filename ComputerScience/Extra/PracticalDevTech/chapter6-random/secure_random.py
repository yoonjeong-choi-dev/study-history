import os
import struct

num_randoms = 10
for i in range(num_randoms):
    # OS에서 제공하는 기능으로 랜덤 4바이트 생성
    random_four_bytes = os.urandom(4)
    # 4바이트 정수 변환하여 출력
    random_integer = struct.unpack("<L", random_four_bytes)[0]
    print("hex= {}, integer= {}".format(random_four_bytes.hex(), random_integer))