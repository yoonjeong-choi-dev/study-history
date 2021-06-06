#!/bin/bash

FILE=/etc/passwd

# 유저 이름 받아오기
read -p "Enter a username to find password : " username

# 입력받은 유저 이름을 통해 passwd 파일에서 해당 정보 저장
file_info=$(grep "^$username:" $FILE) 

# 구분자(IFS)를 통해 정보 출력
if [ -n "$file_info" ]; then
    # :를 구분자로 사용하여, 해당 데이터의 필드 값 추출 
    IFS=":" read user pw uid gid name home shell <<< "$file_info"
    echo "User      = '$user'"
    echo "UID       = '$uid'"
    echo "GID       = '$gid'"
    echo "Full Name = '$name'"
    echo "Home Dir  = '$home'"
    echo "Shell     = '$shell'"
else
    # 해당 유저가 없는 경우 표준 에러 출력으로 리다이렉션
    echo "No such user '$username'" >&2
    exit 1
fi