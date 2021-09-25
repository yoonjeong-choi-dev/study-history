#!/bin/bash

if [ $# -eq 1 ]
then
	if [ -r $1 ]
	then
		echo "파일을 읽습니다."
		cat $1
	else
		echo "존재하지 않는 파일입니다."
		echo "$1 파일을 직접 만들어 봅시다"
		echo "데이터를 입력한 후, Ctrl-C를 입력하세요"
		cat > $1
	fi
else
	echo "파일 이름을 넣지 않았습니다. 다시 실행해 주세요."
fi
