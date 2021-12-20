#!/bin/bash

# 1번 v 옵션 : 컨테이너 내부의 패키지 관련 디렉터리 참조
# 2번 v 옵션 : 현재 디렉터리(개발)에서 스크립트 관련 디렉터리 참조
# => 애플리케이션 관련 스크립트 변경 시, 이미지 빌드 없이 테스트 가능
docker run -d -p 8080:7166 -v /usr/src/app/node_modules -v $(pwd):/yj-node-app docker-ci-study/nodejs-app