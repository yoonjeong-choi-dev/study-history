#!/bin/bash

# << 프로세스가 1개만 돌고 있는지 확인하는 프로그램 >>
#   주석 처리된 echo는 스크립트 자체 실행 시 사용하는 디버그 용
PROCESS_NAME="only-one-proc"

# 인자 확인 : 인자가 1개 필요
if [ $# -eq 1 ]
then
    #echo "인수는 1개이며 내용은 <$1>"
    echo -e "\c"
else
    echo "INVALIDARG"
    exit 0
fi

# 사용자 체크 : root만 유효
user=$(whoami)
if [ $user = root ]
then
    #echo "user is root"
    echo -e "\c"
else
    echo "NOTROOT"
    exit 0
fi

# 옵션 체크
case $1 in
start)
    # 프로세스가 실행 중인지 체크하고 없으면 백엔드에서 실행
    usage=$(ps -a | grep $PROCESS_NAME | awk '{print $4}')
    if [ "$usage" = "$PROCESS_NAME" ]
    then
        echo "ALREADY"
    else
        ./$PROCESS_NAME > /dev/null 2>&1 & 
        echo "RUNNING"
    fi
    ;;
stop)
    # 실행 중인 프로세스 kill
    usage=$(ps -a | grep $PROCESS_NAME | awk '{print $4}')
    if [ "$usage" = "$PROCESS_NAME" ]
    then
        kill $(ps -a | grep $PROCESS_NAME | awk '{print $1}') > /dev/null 2>&1
        echo "STOPONE"
    else
        echo "ANYONEP"
    fi
    ;;
*)
    echo "UNKNOWN ARG"
esac

exit 1