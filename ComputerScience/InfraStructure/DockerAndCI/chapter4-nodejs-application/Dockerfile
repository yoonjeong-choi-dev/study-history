# nodejs 애플리케이션 실행을 위한 베이스 이미지 : 노드 버전 14
FROM node:14

# 애플리케이션 디렉터리 생성
WORKDIR /yj-node-app

# 애플리케이션 실행을 위한 종속성 파일 추가 및 설치 
# : 마이너한 변경의 경우 종속성 파일은 변경 X
# => 코드 변경에 대한 효율적인 이미지 빌드 가능
COPY package*.json ./
RUN npm install ./

# 애플리케이션 실행을 위해 필요한 스크립트 추가 : index.js
# .dockerignore 설정으로 인해 종속성을 제외한 실제 애플리케이션 코드들이 추가됨
COPY . .

# 포트 개방
EXPOSE 7166

# 애플리케이션 실행
CMD ["node", "index.js"]
