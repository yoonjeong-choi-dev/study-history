#!/bin/bash


# file info function
file_info (){
    file_name=$1

    # 해당 파일 존재하는 경우 파일의 타입 및 상태 출력
    if [[ -e $file_name ]]; then
        echo -e "\nFile Type :"
        file $file_name
        echo -e "\nFile Status :"
        stat $file_name
        return 0
    else 
        echo "$FUNCNAME usage : $FUNCNAME filename" >&2 
        return 1
    fi
}


# 쉘 함수 테스트
echo "input : $1"
file_info $1