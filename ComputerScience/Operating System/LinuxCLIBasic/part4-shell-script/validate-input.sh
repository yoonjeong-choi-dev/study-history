#!/bin/bash

invalid_input(){
    if [[ -z $REPLY ]]; then
        echo "Empty input"
    else
        echo "Invalid input : ${REPLY}"
    fi
    exit 1
}

read -p "Enter a single item :"


###############################
# 문자열 검증
###############################
#1 문자열을 입력하지 않은 경우 
[[ -z $REPLY ]] && invalid_input

#2 문자열이 여러 개인 경우
(( $(echo $REPLY | wc -w) >1 )) && invalid_input

# 파일 이름 형식인지 확인
if [[ $REPLY =~ ^[-[:alnum:]\._]+$ ]]; then
    echo "'$REPLY' is a valid filename"

    # 파일 존재 여부 확인
    if [[ -e $REPLY ]]; then
        echo "And file '$REPLY' exists"
    else
        echo "However file '$REPLY' does not exist"
    fi

    # 부동소수점인지 확인 : *.+ 형태
    if [[ $REPLY =~ ^-?[[:digit:]]*\.[[:digit:]]+$ ]]; then
        echo "'$REPLY' is a floating point number"
    else
        echo "'$REPLY' is not a floating point number"
    fi

    # 정수인지 확인
    if [[ $REPLY =~ ^-?[0-9]+$ ]]; then
        echo "'$REPLY' is an integer"
    else
        echo "'$REPLY' is not an integer"
    fi
else
    echo "The string '$REPLY' is not a valid filename"
fi