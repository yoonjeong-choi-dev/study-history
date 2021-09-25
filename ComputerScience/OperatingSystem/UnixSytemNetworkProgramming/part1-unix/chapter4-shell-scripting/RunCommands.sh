#!/bin/bash

# 명령어 이름
commandName=0
# 명령어 옵션 : 옵션은 최대 1개까지만 설정 가능
commandOption=0
# 명령어에 대한 상태
# 0 : 초기상태 1: 명령어 읽은 상태 2: 옵션까지 읽은 상태
complete=0

while [ $# -gt 0 ]
do
	case $1 in
	# 옵션 처리: 옵션읽고 상태 변경
	-*)
		commandOption=$1 ;
		complete=2 ;
		shift ;;
	# 명령어 처리
	*)
		# 명령어 읽지 않은 상태 : 명령어 읽고 상태 변경
		if [ $complete = 0 ]
		then
			commandName=$1
			complete=1
			shift
			
			# 해당 명령어가 마지막인 경우 : 옵션 없음 => 명령어 수행
			if [ $# = 0 ]
			then
				$commandName
			fi
		# 명령어 읽은 상태 : 다음 명령어를 읽기 위해 해당 명령어 실행
		elif [ $complete = 1 ]
		then
			$commandName
			commandName=$1
			shift
			if [ $# = 0 ]
			then
				$commandName
			fi
		fi ;;
	esac

	if [ $complete = 2 ]
	then
		$commandName $commandOption 
		complete=0
	fi
done


