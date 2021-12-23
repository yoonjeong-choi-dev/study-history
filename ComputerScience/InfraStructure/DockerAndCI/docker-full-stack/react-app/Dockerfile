# < 빌드 단계 >
FROM node:alpine as builder  

WORKDIR /yj-react-app

COPY package.json ./

RUN npm install

COPY . .

# 리액트 앱 빌드 : /yj-react-app/build 에 빌드 파일 생성
RUN npm run build

# < 배포 단계 >
FROM nginx
EXPOSE 80

# 빌드 파일 복사
# -from="빌드 스테이지 이름"을 통해 빌드 단계에서의 컨테이너 참조
# nginx : /usr/share/nginx/html 내부 정적 파일을 주소에 맞게 전달
COPY --from=builder /yj-react-app/build /usr/share/nginx/html