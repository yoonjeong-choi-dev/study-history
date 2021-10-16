#!/bin/bash

# df -k 를 이용하여 디스크의 현재 사용률을 출력
usage=`df -k $1 | awk '{rem = 0} {n+=1} {a=$3} {b=$4} \
n==2 {rem = int(a/(a+b) * 100); print rem }\
END { }'`

echo $usage