# npm 사용을 위해 node 베이스 이미지 사용
FROM node:alpine as builder

# 애플리케이션 소스 코드 경로 설정
WORKDIR /yj-react-app

# 모듈 설치를 위한 package.json 복사 및 설치
COPY package.json ./
RUN npm install

# 애플리케이션 소스 복사
COPY ./ ./

# 리액트 앱 빌드
CMD ["npm", "run", "build"]


# 운영 환경에서 사용할 이미지 빌드
FROM nginx
EXPOSE 3000

# nginx 설정 파일 복사 : 프론트엔드 서버에서 정적 파일을 제공하는 역할 설정
COPY ./nginx/default.conf /etc/nginx/conf.d/default.conf

# 빌드 파일 복사
COPY --from=builder /yj-react-app/build /usr/share/nginx/html