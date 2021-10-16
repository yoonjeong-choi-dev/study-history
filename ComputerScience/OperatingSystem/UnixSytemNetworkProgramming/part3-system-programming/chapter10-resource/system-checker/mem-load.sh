#!/bin/bash

# top를 이용하여 전체 메모리와 사용 중인 메로리 크기(Mb) 출력
# top의 3번째 줄 정보
usage=`top -n 1| awk '{rem = 0} {n += 1} {a = $4 } { b = $8 } \
n == 4 {rem = a; print rem "M " b "M"} \
END { }'`

echo $usage