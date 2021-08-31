#!/bin/bash


read -p "Enter a postive integer up to sum : "

# 양의 정수인지 판별
if [[ "$REPLY" =~ ^[0-9]+$ ]]; then
    sum=0
    count=1

    while [ $count -le $REPLY ]; do
        sum=$((sum+count))
        count=$((count+1))
    done
else
    echo "Input value is not a positve interger" >&2
    exit 1
fi

echo "Sum 1 to ${REPLY} : ${sum}"