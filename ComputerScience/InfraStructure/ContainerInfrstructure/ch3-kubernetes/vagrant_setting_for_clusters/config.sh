#!/usr/bin/env bash

################################
# 클러스터 자동 구성을 하는 kubeadm 및 쿠버네티스 설치의 사전 요구 조건 설정
################################

# vim configuration : vim에 대한 별칭 설정
echo 'alias vi=vim' >> /etc/profile

# 쿠버네티스 설치 조건 : 스왑 비활성화
swapoff -a

# 시스템 재시작 시에도 스왑 비활성화되도록 설정
sed -i.bak -r 's/(.+ swap .+)/#\1/' /etc/fstab

# 쿠버네티스 저장소 등록
gg_pkg="packages.cloud.google.com/yum/doc" 
cat <<EOF > /etc/yum.repos.d/kubernetes.repo
[kubernetes]
name=Kubernetes
baseurl=https://packages.cloud.google.com/yum/repos/kubernetes-el7-x86_64
enabled=1
gpgcheck=0
repo_gpgcheck=0
gpgkey=https://${gg_pkg}/yum-key.gpg https://${gg_pkg}/rpm-package-key.gpg
EOF

# SELinux를 permissvie 모드로 설정 : 보안에 어긋나면 로그만 남기는 모드
setenforce 0
sed -i 's/^SELINUX=enforcing$/SELINUX=permissive/' /etc/selinux/config

# 브리지 네트워크를 통화하는 IPv4, IPv6 패킷을 iptables에서 관리
# 쿠버네티스의 경우 POD 통신을 iptables에서 관리
cat <<EOF >  /etc/sysctl.d/k8s.conf
net.bridge.bridge-nf-call-ip6tables = 1
net.bridge.bridge-nf-call-iptables = 1
EOF

# br_netfilter 커널 모듈을 이용하여 브리지 네트워크 구성
# IP 마스커레이드를 사용하여 내부/외부 네트워크 분리
modprobe br_netfilter

# local dns : 노드 간 통신을 위해 노드들의 이름과 IP 등록
echo "192.168.1.10 m-k8s" >> /etc/hosts
for (( i=1; i<=$1; i++  )); do echo "192.168.1.10$i w$i-k8s" >> /etc/hosts; done

# DNS 서버 지정  
cat <<EOF > /etc/resolv.conf
nameserver 1.1.1.1 #cloudflare DNS
nameserver 8.8.8.8 #Google DNS
EOF

