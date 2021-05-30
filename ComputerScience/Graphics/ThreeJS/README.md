# 교재 정보
- Three.js로 3D 그래픽 만들기(저자: 요스 디륵센, 출판:Packt)
- WebGL을 공부하기 전에 웹 그래픽스 프로그래밍을 간단하게 공부하고 싶어 시작

# 코드 정보
- 필요한 라이브러리는 해당 html의 script 태그를 통해 확인 후, libs 폴더에 넣어 주어야 함
	- 불필요한 코드(라이브러리) 중복을 막기위해 제거
- 로컬 테스트를 하는 경우, 로컬 파일 시스템을 직접 수행 불가능
	- 로컬 파일 시스템에서 리소스를 읽어야 하는 코드는 에러 발생
	- npm의 http-server 모듈을 이용하여 웹서버를 구축하고 테스트해야 한다
	- 구축 방법 : https://blog.cjred.net/entry/simple-frontend-dev-webserver-httpserver
	- npm을 환경 변수로 등록해야 한다
