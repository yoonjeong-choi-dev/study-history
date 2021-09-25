#!/bin/bash

if [ $# -ne 1 ] 
then
	echo "usage : DiskUsageCheck.sh [Diskpath]"
	exit 1
fi

usage=`df -k $1 | /bin/awk '{ rem = 0 } { n += 1 } { a = $3 } { b = $4 } \ 
n == 2 { rem = int(a/(a+b) * 100); print rem } \
END { }'`

status="DISk($usage)"

if [ $usage -ge 90 ] 
then
	echo "$status - 심각한 상태"
elif [ $usage -ge 70 ]
then 
	echo "$status - 주의요망 상태"
else
	echo "$status - 양호한 상태"
fi
