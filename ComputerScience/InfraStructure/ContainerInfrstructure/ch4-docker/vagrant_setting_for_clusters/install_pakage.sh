#!/bin/bash

################################
# 클러스터 구성을 위한 의존성 패키지 설치
################################

# 기본 패키지
yum install epel-release -y
yum install vim-enhanced -y
yum install git -y

# Docker 설치 및 실행 : 18.09.9 버전
yum install docker-ce-18.09.9-3.el7 docker-ce-cli-18.09.9-3.el7 \
    containerd.io-1.2.6-3.3.el7 -y
systemctl enable --now docker

# 쿠퍼베니트 설치 및 실행
yum install kubectl-$1 kubelet-$1 kubeadm-$1 -y
systemctl enable --now kubelet

# 마스터 노드의 경우, 설정 파일을 git을 통해 다운받아 놓는다
if [ $2 = 'Main' ]; then
  git clone https://github.com/sysnet4admin/_Book_k8sInfra.git
  mv /home/vagrant/_Book_k8sInfra $HOME
  find $HOME/_Book_k8sInfra/ -regex ".*\.\(sh\)" -exec chmod 700 {} \;
fi