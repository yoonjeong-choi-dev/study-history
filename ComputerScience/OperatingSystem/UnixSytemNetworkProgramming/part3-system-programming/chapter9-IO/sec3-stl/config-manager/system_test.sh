#!/bin/bash

echo "[[ Makefile을 이용하여 시스템 빌드 ]]"
make
echo ""

FILE_NAME="CheckTrace"

echo "[[ 시스템 변수 없이 테스트]] "
./$FILE_NAME
echo ""

echo "[[ 시스템 변수 설정 ]]"
export MY_CONFIG_FILE="./ConfigFile"
echo ""

echo "[[ 시스템 변수를 이용하는 테스트 ]]"
./$FILE_NAME
echo ""

echo "[[ 시스템 변수 해제 ]]"
unset MY_CONFIG_FILE
echo ""

echo "[[ 리소스 정리 ]]"
make clean