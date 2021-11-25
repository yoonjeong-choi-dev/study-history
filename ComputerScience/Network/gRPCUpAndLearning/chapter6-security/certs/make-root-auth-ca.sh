#!/bin/bash

# RSA 2048 비트 비밀 키 생성 (표준)
openssl genrsa -out ca.key 2048

# 인증서 서명 요청(CSR) 작성
openssl req -new -sha256 -key ca.key -out ca.csr -config openssl.cnf

# 인증서를 자신의 비밀로 서명하여 생성
openssl x509 -in ca.csr -days 365 -req -signkey ca.key -sha256 -out ca.crt -extfile ./openssl.cnf -extensions CA