#!/bin/bash

# 컴파일에 사용할 바벨 패키지 설치
# cli : 커맨드 라인을 통해 바벨을 실행시킬 수 있는 바이너리 파일
# preset-react : JSX 문법을 React.createElement로 변환해주는 플러그인
npm install @babel/core @babel/cli @babel/preset-react

# 설치된 패키지를 이용하여 자바스크립트 변환(컴파일)
npx babel --watch src --out-dir . --presets @babel/preset-react
