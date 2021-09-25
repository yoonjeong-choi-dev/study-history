#!/bin/bash

if [ $# -ne 1 ] 
then
	echo "usage : DiskUsageCheck.sh [Diskpath]"
	exit 1
fi

usage=`df -k $1 | /bin/awk '{ rem = 0 } { n += 1 } { a = $3 } { b = $4 } \ 
n == 2 { rem = int(a/(a+b) * 100); print rem } \
END { }'`

echo $usage
