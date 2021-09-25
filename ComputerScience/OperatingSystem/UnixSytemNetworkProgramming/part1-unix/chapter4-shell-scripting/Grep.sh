#!/bin/bash

echo -ne "grep에 사용될 옵션 입력 - -l 또는 -s를 입력하세요: "
read option1
echo -ne "검색하고자 하는 문장을 입력하세요: "
read option2

grep $option1 $option2 *
