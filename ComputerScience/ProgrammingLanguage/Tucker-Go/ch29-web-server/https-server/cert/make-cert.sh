#!/bin/bash

# 인증서 설정 파일을 통해 rsa:2048 방식으로 비밀키 생성 및 인증 파일 생성
openssl req -new -newkey rsa:2048 -nodes -keyout localhost.key -out localhost.csr -config config.cnf

# 인증서 설정 파일을 통해 인증서를 자기 서명(로컬 테스트용)
openssl x509 -req -days 365 -in localhost.csr -signkey localhost.key -out localhost.crt -extfile ./config.cnf -extensions CA