#!/bin/bash

# 리액트 프로젝트를 위한 최소한의 패키지 다운로드 스크립트

# react : 플랫폼과 상관 없는 공통 리액트 라이브러리
wget -N https://unpkg.com/react@16/umd/react.development.js
wget -N https://unpkg.com/react@16/umd/react.production.min.js

# react-dom : 웹에 사용할 수 있는 리액트 라이브러리
wget -N https://unpkg.com/react-dom@16/umd/react-dom.development.js
wget -N https://unpkg.com/react-dom@16/umd/react-dom.production.min.js