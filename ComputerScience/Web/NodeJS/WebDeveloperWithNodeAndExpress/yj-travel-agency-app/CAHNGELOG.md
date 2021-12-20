## Changelog

각 챕터 별, 추가/변경 사항 작성

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
