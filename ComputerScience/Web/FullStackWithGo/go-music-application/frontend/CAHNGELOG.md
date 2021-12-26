## Changelog

각 챕터 별, 추가/변경 사항 작성

### [0.2.0]

> Chapter 5. Go Music Frontend

- Go Music 앱의 프론트엔드 구현
- public/ 내부에 서버에서 fetch할 데이터를 우선 로컬로 저장
- 컴포넌트와 페이지 디렉터리 분리
  - 컴포넌트 : 리액트 컴포넌트
  - 페이지 : 라우터에서 렌더링할 각 페이지
- 모달 컴포넌트(/component/modals)
  - reactstrap 패키지 이용하여 구현
  - 로그인/회원 가입 모달
    - 로그인한 경우, App 컴포넌트의 로그인 상태 변경
  - 신용 카드 결제 모달
    - 스트라이프 서비스 이용 : https://stripe.com/docs/testing
      - 교재처럼하면 토큰 생성이 안됨
      - 스트라이프 라이브러리 @stripe/react-stripe-js, @stripe/react-stripe 사용해야 한다
      - https://pretagteam.com/question/how-can-i-create-token-using-stripejs-and-reactjs 참조
    - 이후 백엔드와 연동 필요
- 로그인 여부에 따라 렌더링/라우터 설정

### [0.1.0]

> Chapter 4. React Tutorial

- Go Music 앱의 프론테엔드 시작
- 초기 구성
  - CRA에서 불필요한 파일 제거
  - index.js에 bootstrap 관련 CSS 및 JS 임포트
- 로컬에서 사용할 리소스들을 public 하위 디렉터리에 추가
  - /img에 프로젝트에 사용할 악기 사진
  - 악기 정보가 저장된 Cards.json
- index.js에 Card 컴포넌트 구현 및 추가