#!/usr/bin/env bash

# 마스터 노드에서 설정한 토큰과 ip를 통해 마스터 노드에 조인
kubeadm join --token 123456.1234567890123456 \
             --discovery-token-unsafe-skip-ca-verification 192.168.1.10:6443