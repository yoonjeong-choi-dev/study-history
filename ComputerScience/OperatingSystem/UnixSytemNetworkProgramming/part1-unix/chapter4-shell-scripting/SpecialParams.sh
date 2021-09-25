#!/bin/bash

echo "grep 을 위한 쉘 프로그램이 실행"
echo "이 프로그램의 PID : $$"
echo "입력한 인수의 개수 : $#"
echo "인수의 전체 내용 : $*"
echo "입력한 인수를 이용하여 grep을 백그라운드로 실행"
grep $* * &
echo "grep의 백그라운드 PID : $!"
