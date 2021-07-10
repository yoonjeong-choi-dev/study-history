#!/bin/bash

chmod +x prog1-inpath.sh

echo "./prog1-inpath.sh echo : echo 명령어 검사"
./prog1-inpath.sh echo

echo "./prog1-inpath.sh /usr/bin/echo : echo 절대 경로에 대한 검사"
./prog1-inpath.sh /usr/bin/echo

echo "./prog1-inpath.sh intro.sh : PATH에 저장되어 있는 my-bash-script 경로에 대한 검사"
./prog1-inpath.sh intro.sh