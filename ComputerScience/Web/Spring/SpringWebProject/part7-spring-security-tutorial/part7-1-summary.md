# (1) 스프링 시큐리티

## Chapter 30. Spring Web Security
### 필터와 인터셉터
* 스프링 시큐리티의 기본 동작 방식은 필터와 인터셉터를 사용
* 필터와 인터셉터는 특정 서블릿이나 컨트롤러의 접근을 관여한다는 유사점 존재
* 필터
  * 서블릿에서 말하는 필터
  * 서블릿의 호출 흐름을 관여
  * AOP 처럼 서블릿 기능 수행 전후에 처리하는 기능을 담당
  * 스프링과 무관한 자원
* 인터셉터
  * 스프링의 빈으로 관리되면서 스프링의 컨텍스트 내에 존재
  * 스프링의 컨텍스트에 있는 모든 자원 활용 가능
* 스프링 시큐리티는 별도의 컨텍스트를 생성하여 처리
  * 스프링과 관련된 컨텍스트
    * 시큐리티 컨텍스트
    * 웹 어플리케이션 컨텍스트(servlet-context.xml)
    * 루트 컨텍스트(root-context.xml)
  * 스프링 컨텍스트는 스프링과 관련된 컨텍스트 영역들에 존재하는 빈들을 이용하여 인증 처리 가능

### 스프링 시큐리티의 동작
* 인증과 권한 부여
  * 인증(Authentication)
    * 사용자가 자신을 증명하는 것
    * 자기 스스로 자신을 증명하기 위한 데이터를 서버에 제시
  * 권한 부여/인가(Authorization)
    * 남(서버)에 의해서 자격이 부여되는 것
    * 인증된 사용자에 대해서 특정 기능에 대한 사용 권한이 있는지 확인 후 해당 권한을 부여하는 것
* 스프링 시큐리티의 인증 및 권한 부여
  * AuthenticationManager(인증 매니저)
    * 인증을 처리하는 방법을 정의한 인터페이스 i.e 인증 처리를 위한 API 정의
    * 구현체를 통해 다양한 인증 처리를 위임
  * AuthenticationProvider(인증 제공자)
    * 실제 인증 작업 진행
    * 서블릿 필터에 의해 동작
    * 인증된 정보에 권한에 대한 정보를 같이 전달
    * UserDetailsService 인터페이스
      * AuthenticationProvider에서 사용하는 인터페이스
      * 실제 사용자의 정보 및 권한 정보를 처리하여 반환하는 기능 정의
* 개발자가 스프링 시큐리티를 커스터마이즈하는 방식
  * AuthenticationProvider 직접 구현
    * 새로운 프로토콜이나 인증 구현 방식을 직접 구현해야 하는 경우
  * UserDetailsService 구현
    * 실제 인증을 담당하는 인터페이스를 구현하는 방식
    * 대부분의 경우 해당 방식 사용

### Spring Web Security 튜토리얼 프로젝트 구성
* 스프링 시큐리티 관련 라이브러리 추가
  * 현재 스프링보다 낮은 버전으로 web, config, core 의존성 추가
  * 스프링 시큐리티 관련 태그 라이브러리 추가
* 스프링 시큐리티 설정
  * 별도의 xml 파일을 통해 설정
    * authentication-manager 등록
    * 시작 지점 설정
  * web.xml 에 스프링 시큐리티 필터 등록
    * 스프링에 의해 생성되는 필터 이름은 springSecurityFilterChain
    * 필터 설정 시, filter-name 은 springSecurityFilterChain 로 반드시 설정
    * 해당 필터 서블릿 필터에 해당하는 클래스는 DelegatingFilterProxy
      * 스프링의 애플리케이션 컨텍스트에서 얻은 Filter Bean 객체를 실행하는 것
      * 스프링 시큐리티 필터에 대한 빈 설정이 없는 경우, 기본적으로 이름은 springSecurityFilterChain
* 예제 코드 AuthController
  * 특정 권한에 따라 접근 가능한 url 통제
    * all : 모든 사용자
    * member : 로그인한 유저
    * admin : 관리자 권한이 있는 로그인 유저


## Chapter 31. 로그인 및 로그아웃
### 접근 제한 url 및 유저 권한 설정
* 접근 제한
  * security:intercept-url 이용하여 특정 url 패턴에 대한 인터셉터 설정
  * access 속성을 이용하여 권한 체크
    * UserDetailsService를 이용하여 인증 및 권한 처리
  * 접근이 제한된 url 접근 시, 스프링 시큐리티가 제공하는 기본 로그인 페이지로 이동
    * security:form-login 태그의 기본 속성
    * login-page 속성을 이용하여 커스텀 로그인 페이지 설정
* 로그인 처리를 위한 유저 등록
  * 스프링 시큐리티 용어
    * username : 일반 시스템에서 사용하는 사용자 아이디
    * User : 스프링 시큐리티에서 사용하는 인증 정보와 권한을 가진 객체
  * security:user-service 태그 내에 유저의 아이디, 비밀번호, 권한을 설정하여 등록 가능
* 로그인 유지 방식
  * WAS에서 사용하는 세션 쿠키 이용
  * 톰캣의 경우 JSESSIONID 이용
* 접근 제한 페이지 접속 시 에러
  * 로그인 한 유저가 권한이 없는 페이지 접근 시 기본적으로 WAS 403 에러 페이지 출력
  * security:access-denied-handler 태그를 이용
    * error-page 설정
      * 특정 url에 대한 컨트롤러 연결
      * 에러 페이지로 이동 시, 사용자가 접근했던 페이지의 url 유지
    * AccessDeniedHandler 인터페이스 구현
      * 접근 제한에 대해 다양한 처리를 하는 경우 사용
      * 쿠키나 세션에 특정 작업
      * HttpServletResponse 객체를 이용하는 경우 &rightarrow; 서블릿 API 사용 가능
        * 특정 헤더 추가
        * 리다이렉션

### 커스텀 로그인 페이지
* security:form-login 태그의 login-page 속성 이용
  * 설정 방식은 접근 제한 페이지와 비슷
    * login-page 속성에 설정한 url로 GET 호출
    * AuthenticationSuccessHandler 인터페이스 구현
      * 로그인 성공 이후 특정 작업을 추가해야 하는 경우 사용
  * 컨트롤러에서 로그인 페이지 설정
* 로그인 페이지 특징
  * 로그인 폼은 `POST /login` 방식으로 데이터 전송
  * 전송하는 데이터들의 키 이름은 username/password
  * hidden input 값으로 CSRF 토큰 저장
    * 스프링 시큐리티가 적용된 모든 페이지에서의 POST 요청은 CSRF 토큰 이용
* CSRF(Cross-site request forgery) 공격
  * 사이트간 요청 위조
  * 서버가 받은 요청을 처리할 때 어떤 출저에서 호출이 진행되었는지 검증을 하지 않는 약점을 이용한 공격
  * 공격 예시
    * A 사이트의 관리자가 피해자
    * 공격자는 A 사이트에서 특정 사용자의 권한을 변경하는 URI 알고 있는 상황
    * 공격자는 관리자가 자주 가는 페이지에 해당 URI를 추가한 img 나 form 태그를 추가한 게시물 작성
    * 관리자가 해당 게시물 접근 시, URI 호출
    * 관리자가 로그인 한 상태면 정상적으로 URI 요청이 처리되면서 공격자의 권한이 변경
  * 일반적인 방어 방법
    * 사용자 요청에 출처에 해당하는 referer 헤더 확인
    * 보안해야 하는 특정 작업(관리자 변경 등)에 대해서 PUT/DELETE 등의 메서드 이용
    * 토큰 사용
  * CSRF 토큰
    * 서버에서 브라우저로 데이터를 전송할 때 난수로 생성한 토큰을 함께 전송
    * 해당 페이지에서 특정 요청을 할때 토큰을 같이 전송하고, 서버는 토큰 값을 비교하여 검증
    * 토큰을 주고받음으로써 응답한 페이지와 다른 페이지에서는 요청 위조 불가능
      * 공격을 위해서는 난수로 생성된 토큰 값을 알아야 함
      * 위 방식처럼 정적인 내용의 img/form 태그 사용 불가능
* 로그아웃 처리
  * security:logout 태그를 이용하며 로그인 처리와 비슷
    * URI 지정 방식
    * LogoutSuccessHandler 인터페이스 구현
  * URI 지정 시, 로그아웃 폼 뷰를 반환하는 GET 컨트롤러 접근
    * 로그아웃 폼에서는 같은 이름의 URI로 POST 요청
    * POST 요청이기 때문에 CSRF 토큰 필요