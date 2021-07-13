#!/bin/bash

# HTTP/2 기능을 제어하는 GODEBUG 환경 변수 설정
go_file="negotiation-http2.go"

echo "Original Test"
go run $go_file
echo ""

echo "http2client=0 : 클라이언트의 HTTP/2 지원을 무효로 한다"
GODEBUG=http2client=0 go run $go_file
echo ""

echo "http2server=0 : 서버의 HTTP/2 지원을 무효로 한다"
GODEBUG=http2server=0 go run $go_file
echo ""

echo "http2debug=1 : HTTP/2 관련 디버그 로그 활성화"
GODEBUG=http2debug=1 go run $go_file
echo ""