#!/bin/bash

# 라이브러리를 만들기 위해 오브젝트 파일(makeMsg.o) 생성
cc -c makeMsg.c

# 생성된 오브젝트 파일을 이용하여 라이브러리 만들기
ar crv libMsg.a makeMsg.o

# 라이브러리를 이용하여 메인 코드의 실행 파일 빌드
cc -o useMsg useMsg.c libMsg.a

# 테스트 
echo "Request Test"
./useMsg req

echo "Response Test"
./useMsg res

echo "Unvalid Type Test"
./useMsg qwer

# 리소스를 정리하자!
rm libMsg.a makeMsg.o useMsg