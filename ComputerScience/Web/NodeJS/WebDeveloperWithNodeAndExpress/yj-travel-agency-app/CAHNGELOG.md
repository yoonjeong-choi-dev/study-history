## Changelog

각 챕터 별, 추가/변경 사항 작성

### [0.9.0]

> Chapter 13. Database
- 이미지 로컬 업로드 구현
- 각 db에서 유저 설정 방식 설명
- mysql
  - CREATE USER 'expressuser'@'localhost' IDENTIFIED BY 'expressuser';
  - create database expressdb;
  - grant all privileges on expressdb.* to 'expressuser'@'localhost';
  - flush privileges;
- mongodb
  - sudo systemctl start mongod
  - use express_test
  - db.createUser({user: 'expressuser', pwd: 'expressuser',  roles: [{ role: "dbOwner", db: "express_test" }]})
- lodash
  - DB 스키마는 스네이크 케이스, js는 카멜 케이스를 사용
  - 스네이크 <-> 카멜 케이스를 변환해주는 라이브러리


### [0.8.0]

> Chapter 12. Production Environment

- 서버 시작 시, 현재 환경 출력
  - 표준 환경은 개발, 실무, 테스트
  - 모든 미들웨어 및 익스프레스는 위 3개의 환경이 있다고 가정하고 동작
- 로그 미들웨어 morgan 추가
  - 개발 환경에서는 콘솔 로그 출력
  - 실무 환경에서는 로그 파일 생성하여 기록
- 클러스터를 이용한 스케일 아웃
  - cluster.js를 이용하여 CPU 최대 코어만큼 노드 앱 실행
  - index.js에서 개발 환경인 경우, 워커노드의 ID 출력
  - 서버가 다운되는 상황(`GET /server-down`)에서 클러스터는 종료된 워커 노드에 대해 새로운 워커 노드 생성
- 익스프레스에서 처리하지 못하는 예외에 대한 처리
  - uncaughtException 이벤트 내에서 예외 처리
  - index.js에 해당 이벤트 핸들러 추가
- package.json의 스크립트 변경
  - 실무 환경은 NODE_ENV 환경변수 변경
  - 클러스터 실행 스크립트 추가 `npm run cluster`
  

### [0.7.0]

> Chapter 11. Email

- 이메일 주소 검증 함수를 유틸 파일에 모듈화
- sendgrid 서비스를 이용한 메일 전송 서비스
  - .env에 sendgrid API Key 추가
  - sendgrid 인증을 위한 nodemailer-sendgrid 패키지 설치
  - /newsletter-signup 서비스 감사 메일 전송 프로세스 추가
- nodemailer 패키지를 이용하여 메일 전송 라이브러리(email.js) 추가
  - html-to-formatted-text 패키지를 이용하여 html을 텍스트 버전으로 생성
  - sendgrid 설정을 한 nodemailer 인스턴스의 sendMail 프로미스를 래핑한 프로미스 반환
  - from에 사용하는 이메일은 sendgrid에서 api 키 발급 시 사용한 이메일
- 이메일 폼(.handlebar) 생성
  - http://htmlemailboilerplate.com/ 의 html 보일러플레이트 사용하여 메일폼 생성
  - res.render에 콜백 인자를 넣어 줘서 메일로 전송할 html 렌더링


### [0.6.0]

> Chapter 10. Middleware

- 쇼핑 카트 정보를 관리하는 미들웨어 추가
  - 카트 정보는 세션을 이용하여 저장
  - 쇼핑 카트 정보에 대한 검증을 하는 미들웨어
  - 세션 초기화 -> 동의서 요구 확인 -> 게스트 인원 확인 순서
- 쇼핑 카트 예제를 위한 뷰 파일(shopping) 및 핸들러 추가
  - 미들웨어를 통해 에러/경고 플레시 메시지 구현


### [0.5.0]

> Chapter 9. Cookie and Session

- 쿠키 시크릿 추가
  - .env 파일에 쿠키 암호화를 위한 비밀키 세팅
  - .env 파일을 로드하기 위한 dotenv 패키지 설치
- 쿠키 사용을 위한 cookie-parser 설치
  - 쿠키 시크릿을 이용하여 미들웨어 사용
  - res 객체에서 쿠키 사용 가능
  - 쿠키 및 서명된 쿠키 테스트를 위한 /cookie-test 라우터 추가
- 세션 쿠키를 위한 express-session 설치
  - 세션 Id만 쿠키에 저장하고, 세션 정보는 서버에 저장
  - 현재는 인메모리에 저장하는 방식
  - 쿠키 사용을 위해 쿠키 미들웨어 이후에 설정 필요
  - req.session 을 통해 세션 정보에 접근
- 세션을 사용한 플레시 메시지 예제
  - 플래시 메시지를 req 객체를 이용하여 전달하는 flash.js 미들웨어 추가
  - 레이아웃 파일에서 플래시 메시지를 위한 컴포넌트 추가
    - bootstrap의 플래시 메시지를 이용하기 위해 jQuery 및 bootstrap 관련 js 임포트
  - 메일 가입 신청 핸들러 newletterSignupProcess 수정
    - 이전에는 신청 성공/실패 여부에 따라 다른 페이지로 리다이렉트
    - 성공 여부 관련 없이 하나의 페이지로 리다이렉트
    - Post 성공 여부에 따라 req.session.flash에 메시지 저장하여 렌더링


### [0.4.0]

> Chapter 8. Handle Form Data

- 일반적인 폼 처리를 위해 전송된 인코드된 바디를 분석하는 미들웨어인 body-parser 설정
  - `req.body`를 통해 클라이언트에서 전송된 body 데이터 사용 가능
  - express4부터 express에 body-parser가 내장되어 있음
- 파일 전송 위한 멀티파트 폼 처리를 하는 multiparty 미들 웨어 설치
- CSS 스타일을 부트스트랩 스타일로 적용
  - https://getbootstrap.com/docs/4.1/getting-started/introduction/
  - 디폴트 레이아웃 파일인 `defaultLayout.handlebars`에 css 동적 추가
- 두 가지 방식의 폼처리 방식을 위한 뷰 파일 추가
  - 폼 처리 방법
    - 방법 1 : 브라우저의 폼 액션을 사용하여 서버 응답을 렌더링
    - 방법 2 : 브라우저 폼 액션 대신 fetch(AJAX)를 사용하여 폼 데이터를 직접 전송
  - 폼 방식 
    - 일반 폼 처리 : 메일링 리스트 관련 뷰 파일 추가(newsletter)
    - 멀티파트 폼처리 : 사진 업로드 뷰 파일 추가(contest)

  
### [0.3.0]

> Chapter 5. QA - Test

- QA 유지 모듈 추가
  - 단위 테스트
    - jest 
  - 통합 테스트
   - puppeteer
   - portfinder
  - eslint
- jest 단위 테스트
  - package.json에서 test 스크립트 추가
    - `npm test`
  - 단위 테스트를 위해 라우트 핸들러를 분리
  - lib/__tests__ 디렉터리에 단위 테스트 구현
  - 각 테스트에 필요한 인자(req, res, req, next)에 대해 모킹 구현
  - 코드 커버리지
    - `npm test -- --coverage`
- 통합 테스트
  - 통합 테스트를 위해 index 페이지에 about 페이지 링크 추가
    - data-test-id 데이터 속성을 추가하여 테스트 시 사용
  - 테스트 시 index.js의 app 사용을 위해 app 모듈화 추가
  - integration-tests 디렉터리에 통합 테스트 구현
- eslint
  - 코드 자체에 대한 취약점 분석
  - ES 린트 설정 파일 생성
    - `./node_modules/.bin/eslint --init`
    - airbnb 스타일 적용 및 js 파일로 생성
  - package.json에서 lint 스크립트 추가
    - index.js 및 lib 디렉터리 내부 스크립트에 대해서 lint
  - lint 분석에 대해 코드 수정

### [0.2.0]

> Chapter 4. Best Practice & Versioning

- 포츈 쿠키 기능 모듈화
  - 모듈화 스크립트를 저장하는 lib 디렉터리 추가
  - index.js에 있던 기능을 모듈화

### [0.1.0]

> Chapter 3. Express Tutorial

- 여행사 앱 환경 설정 및 베이스 코드 작성
  - 개발 시 사용할 nodemon 설치 및 package.json 설정
  - `npm run dev`
- 뷰 엔진 Handlebar 설정
  - views 디렉터리에 뷰 관련 파일 추가
- 정적 리소스 관리를 위한 static 미들웨어 사용
