#!/usr/bin/env bash

# 인증서 설정파일(tls.csr)을 이용하여 인증서를 배포하고 레지스트리를 구동하는 셸 스크립트

# 도커는 /etc/docker/certs.d/ 하위 디렉경로에서 레지스트리 주소와 일치하는 디렉터리의 인증서를 찾음
# 찾은 인증서와 함께 레지스트리에 HTTPS로 접속 
certs=/etc/docker/certs.d/192.168.1.10:8443


# 바인드 마운트를 위한 디렉터리 생성
mkdir /registry-image       # 이미지 저장을 위한 바인드 마운트 디렉터리
mkdir /etc/docker/certs     # 레지스트리 내부 인증서 저장을 위한 바인드 마운트 디렉터리

mkdir -p $certs             # 도커에서 참조할 인증서 디렉터리 

# HTTPS 통신을 위한 TLS 인증서 및 암호화/복호화 키 생성 : 자체 서명 인증서
openssl req -x509 -config $(dirname "$0")/tls.csr -nodes -newkey rsa:4096 \
-keyout tls.key -out tls.crt -days 365 -extensions v3_req

# SSH 접속을 위한 비밀번호를 자동 입력하는 라이브러리 설치
yum install sshpass -y

# 워커 노드에 인증서 관련 설정 반복
for i in {1..3}
  do
    # SSH 접속 비밀번호인 vagrant를 워커 노드에 전달하고, 인증서 저장을 위한 디렉터리 생성
    sshpass -p vagrant ssh -o StrictHostKeyChecking=no root@192.168.1.10$i mkdir -p $certs
    # 인증서를 해당 디렉터리에 복사(scp)
    sshpass -p vagrant scp tls.crt 192.168.1.10$i:$certs
  done

# 인증 관련 파일 이동
cp tls.crt $certs
mv tls.* /etc/docker/certs

# 도커 레지스트리 컨테이너 생성
docker run -d \
  --restart=always \
  --name registry \
  -v /etc/docker/certs:/docker-in-certs:ro \
  -v /registry-image:/var/lib/registry \
  -e REGISTRY_HTTP_ADDR=0.0.0.0:443 \
  -e REGISTRY_HTTP_TLS_CERTIFICATE=/docker-in-certs/tls.crt \
  -e REGISTRY_HTTP_TLS_KEY=/docker-in-certs/tls.key \
  -p 8443:443 \
  registry:2
