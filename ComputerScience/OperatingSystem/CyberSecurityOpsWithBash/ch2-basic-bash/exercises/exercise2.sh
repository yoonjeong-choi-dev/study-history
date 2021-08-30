#!/bin/bash

function os_dect(){
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
}

os_dect

echo $OS