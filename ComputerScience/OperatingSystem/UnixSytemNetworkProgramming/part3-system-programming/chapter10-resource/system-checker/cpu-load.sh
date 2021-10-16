#!/bin/bash

# vmstat을 이용하여 전체 cpu의 idle 백분율 출력
# vmstat의 3번째 줄 정보
usage=`vmstat | awk '{rem = 0} {n += 1} {a = $15} \
n == 3 {rem = a; print rem} \
END { }'`

echo $usage