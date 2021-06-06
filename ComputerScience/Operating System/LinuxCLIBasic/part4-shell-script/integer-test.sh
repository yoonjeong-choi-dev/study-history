#!/bin/bash

# 사용자가 입력한 정수에 대해 양수/음수 및 홀수/짝수 판단

# 사용자 입력 1 : echo 로 프롬프트 문자열 생성
#echo -n "Please enter an intager : "
#read int

# 사죵자 입력 2 : -p 옵션을 통해 프롬프트 문자열 생성
read -p "Please enter an intager : " int


# 정수인지 판별
if [[ "$int" =~ ^-?[0-9]+$ ]]; then
    if [ $int -eq 0 ]; then
        echo "$int is zero"
    else   
        if [ $int -lt 0 ]; then
            echo "$int is negative"
        else
            echo "$int is postivie"
        fi

        if [ $((int % 2)) -eq 0 ]; then
            echo "$int is even"
        else
            echo "$int is odd"
        fi
    fi
# 정수가 아닌 경우 표준 에러로 리다이렉션
else
    echo "Input value is not an interger" >&2
    exit 1
fi