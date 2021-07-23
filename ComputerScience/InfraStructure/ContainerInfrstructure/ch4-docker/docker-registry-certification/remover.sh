#!/usr/bin/env bash

# 인증 문제 발생 시, 관련 인증 설정을 모두 삭제하는 셸 스크립트

certs=/etc/docker/certs.d/192.168.1.10:8443

# 기생성했던 디렉터리들 삭제
rm -rf /registry-image
rm -rf /etc/docker/certs
rm -rf $certs

yum -y install sshpass

# 워커 노드에 설정된 인증 설정 삭제
for i in {1..3}
  do
    sshpass -p vagrant ssh -o StrictHostKeyChecking=no root@192.168.1.10$i rm -rf $certs
  done

yum remove sshpass -y
docker rm -f registry
docker rmi registry:2
