#!/bin/bash

# 트랩 설정 : 종료 신호를 받으면 해당 문자열 출력하고 종료하지 않음
trap "echo 'I am ignoring your input'" SIGINT SIGTERM

for i in {1..5}; do
    echo "Iteration $i of 5"
    sleep 5
done