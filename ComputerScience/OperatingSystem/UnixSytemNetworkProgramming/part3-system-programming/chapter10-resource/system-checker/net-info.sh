#!/bin/bash

# netstat -nr를 이용하여 네트워크 인터페이스 정보 출력
usage=`netstat -nr | awk '{rem=0} {n +=1 } {a = $1} {b = $2} {c = $8} \
n > 2 {rem=c; printf "{Name: %s, Net/Dist: %s, Gateway: %s}", rem, a, b} \
END {}'`

echo $usage