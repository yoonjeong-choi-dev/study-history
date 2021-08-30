#!/bin/bash

# MS-Windows/Linux/macOS를 구분
# 사용법 : bash os-detect.sh
# 출력 : MSWin, Linux, macOS 중 하나.


# -t 옵션을 통해 명령어가 존재하면 true 반환
# 모든 출력은 /dev/null로 보내서 폐기

# wevutil 명령어 존재 여부 판정
if type -t wevtutil &> /dev/null
then
    OS=MSWin
# scutil 명령어 존재 여부 판정
elif type -t scutil &> /dev/null
then
    OS=macOS
else
    OS=Linux
fi

echo $OS