#!/usr/bin/env bash

# 워커 노드가 연결될 수 있도록 마스터 노드 설정
# 1. 연결을 위한 토큰 설정
# 2. 쿠버네티스가 자동으로 컨테이너에 부여하는 네트워크 서브넷 설정
# 3. 마스터 노드의 api 호출을 위한 마스터 노드 IP 설정
kubeadm init --token 123456.1234567890123456 --token-ttl 0 \
--pod-network-cidr=172.16.0.0/16 --apiserver-advertise-address=192.168.1.10 

# 쿠버네티스가 기본으로 제공하는 설정 파일을 사용자 디렉터리 내부로 복사 및 권한 설정
# => 사용자가 쿠버네티스 설정 권한을 가지게 된다
mkdir -p $HOME/.kube
cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
chown $(id -u):$(id -g) $HOME/.kube/config

# 컨테이너 네트워크 인터페이스(CNI) 설정
kubectl apply -f \
https://raw.githubusercontent.com/sysnet4admin/IaC/master/manifests/172.16_net_calico.yaml