#!/bin/bash

# FILE에 해당하는 파일 검사
FILE=~/.bashrc


# 파일이 존재하는 경우에만 테스트
if [ -e "${FILE}" ]; then
    if [ -f "$File" ]; then
        echo "$File is a regular file"
    fi
    if [ -d "$FILE" ]; then
        echo "$FILE is a directory"
    fi
    if [ -r "$FILE" ]; then
        echo "$FILE is readable"
    fi
    if [ -w "$FILE" ]; then
        echo "$FILE is writable"
    fi
    if [ -x "$FILE" ]; then
        echo "$FILE is executable/searchable"
    fi
else    
    echo "$FILE does not exist"
    exit 1
fi


exit