#!/bin/bash

# 공개키 및 개인키 생성
openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout yjchoi.pem -out yjchoi.crt 