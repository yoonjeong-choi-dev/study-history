# node 사용을 위해 node 베이스 이미지 사용
FROM node:alpine

# 애플리케이션 소스 코드 경로 설정
WORKDIR /yj-node-app

# 모듈 설치를 위한 package.json 복사 및 설치
COPY package.json ./
RUN npm install

# 애플리케이션 소스 복사
COPY ./ ./

# 노드 서버 실행 명령어
CMD ["npm", "run", "start"]