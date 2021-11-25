#!/bin/bash

# RSA 2048 비트 비밀 키 생성 (표준)
openssl genrsa -out server.key 2048

# 인증서 서명 요청(CSR) 작성
openssl req -new -nodes -sha256 -key server.key -out server.csr -config openssl.cnf

# 인증서를 자신의 비밀로 서명하여 생성
openssl x509 -req -days 365 -in server.csr -sha256 -out server.crt -CA ca.crt -CAkey ca.key -CAcreateserial -extfile ./openssl.cnf -extensions Server