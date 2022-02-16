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


## Chapter 32. JDBC를 이용한 인증/권한 처리
### JDBC를 이용하는 인증 방식
* 스프링 시큐리티의 인증 및 인가 과정
  * 인증과 권한에 대한 처리는 Authentication Manager 이용
  * Authentication Manager는 인증 권한 정보를 제공하는 존재(Provider) 필요
    * 이 존재는 UserDetailsService 인터페이스의 구현체
    * 스프링 시큐리티는 다양한 구현 클래스를 이미 구현하여 제공
    * 이전 챕터에서 security:user-service 태그를 통해 등록한 형태는 InMemoryDetailsManager 클래스를 이용한 것
* JDBC 이용을 위한 테이블 설정 방법
  * 지정된 형식으로 테이블 생성
  * 기존 데이터베이스 이용

### 스프링 시큐리티에서 지정한 SQL 사용하여 테이블 생성
* 테이블 생성 쿼리
  * 유저 테이블
  ```
  create table users
  (
    username varchar(50) not null primary key,
    password varchar(255) not null,
    enabled  boolean      not null default true
  ) ENGINE=InnoDB;
  ```
  * 권한 테이블
  ```
  create table authorities
  (
    username varchar(50) not null,
    authority varchar(50) not null,
    constraint fk_authorities_users foreign key (username) references users (username),
    unique index ix_auth_username(username, authority)
  ) ENGINE=InnoDB;
  ```
  * 유저 데이터 생성
  ```
  insert into users (username, password) values ('user00', 'user00');
  insert into users (username, password) values ('member00', 'member00');
  insert into users (username, password) values ('admin00', 'admin00');
  
  insert into authorities (username, authority) value ('user00', 'ROLE_USER');
  insert into authorities (username, authority) value ('member00', 'ROLE_MEMBER');
  insert into authorities (username, authority) value ('admin00', 'ROLE_MEMBER');
  insert into authorities (username, authority) value ('admin00', 'ROLE_ADMIN');
  ```
* security-context.xml 설정
  * Provider로 JdbcUserDetailsManager 클래스 등록
    * security:authentication-provider 태그 내에 security:jdbc-user-service 태그를 사용하여 등록
    * data-source-ref 속성을 이용하여 데이터 소스에 해당하는 스프링 빈 객체 등록
  * 인증/권한이 필요한 URI 접속 시, 별도 처리없이 위에서 생성한 테이블로 필요한 쿼리 호출
* PasswordEncoder 문제
  * 버전 5부터는 반드시 PasswordEncoder 지정 필요
    * 패스워드 인코딩 처리 시, PasswordEncoder 인터페이스를 이용하여 인코딩
    * 로그인 과정에서 인코딩 처리가 따로 필요
  * 간단한 예제를 위해 인코딩 처리를 안하는 방법
    * 버전 4까지는 별도의 인코딩 처리를 하지 않는 구현체 제공
    * 버전 5부터는 따로 구현하여 사용(CustomNoOpsPasswordEncoder)
      * 시큐리티 컨텍스트 설정 내부에 스프링 빈 등록

### 기존 테이블에 대해서 스프링 시큐리티 이용
* 일반적으로 사용하는 회원 및 권한 관련 테이블 쿼리
  * 유저 테이블
  ```
  create table member
  (
    user_id varchar(50) not null primary key,
    user_pw varchar(100) not null,
    user_name varchar(100) not null,
    registered_date datetime default CURRENT_TIMESTAMP,
    modified_date   datetime default CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    enabled  boolean      not null default true
  ) ENGINE = InnoDB default character set = utf8;
  ```
  * 권한 테이블
  ```
  create table member_auth
  (
    user_id varchar(50) not null,
    auth varchar(50) not null,
    constraint fk_member_auth foreign key (user_id) references member (user_id)
  ) ENGINE = InnoDB default character set = utf8;
  ```
* security-context.xml 설정
  * 기존 테이블을 이용하고 싶은 경우, 스프링 시큐리티에서 지정된 결과를 반환하는 쿼리를 추가하는 작업 필요
  * security:jdbc-user-service 태그 속성을 이용하여 쿼리 지정
    * users-by-username-query : 일반 시스템에서의 유저 Id
    * authorities-by-user-name-query : 특정 유저 Id에 대한 권한 정보
    * 속성 값은 PreparedStatement 구문 이용
* PasswordEncoder 등록
  * 기본적으로 암호 데이터를 데이터베이스에 저장 시 원본을 해싱하여 저장
    * 서버 측에서도 사용자의 암호를 알지 않도록 하는 과정
    * 사용자의 입력과 데이터베이스의 데이터에 대한 해시값을 사용하여 비교
  * 스프링 시큐리티에서 제공하는 BcryptPasswordEncoder 클래스를 이용하여 사용 가능
    * 시큐리티 컨텍스트에 빈으로 등록하여 사용
  * 테스트 코드 작성(com.yj.security.MemberTests)
    * 해시 처리가된 비밀번호를 가진 사용자 추가(testInsertMember)
    * 추가된 사용자에 대해 권한 추가


## Chapter 33. 커스텀 UserDetailsService
### UserDetailsService 인터페이스
* JDBC 이용하는 방식의 단점
  * 사용자의 제한된 정보만 이용
  * 기본적인 방식에서는 username 정보만을 이용하여 사용자 인증
* UserDetailsService 인터페이스 구현
  * UseDetails 인터페이스를 반환하는 메서드 1개로 정의
  * UseDetails 인터페이스
    * 사용자의 자세한 정보를 반환하는 메서드들로 구성
    * 직접 구현하여 사용 가능
    * 스프링 시큐리티에서 제공하는 구현 클래스 사용 가능
  * 일반적으로는 구현 클래스인 User 클래스를 상속받는 형태로 사용
### 구현
* 회원 정보를 이용하기 위한 모델 설계
  * 기존에 구성한 2개의 테이블(유저 정보, 유저 권한)에 대한 VO 클래스
  * Mapper 인터페이스 및 쿼리
* 커스텀 유저 서비스 구현
  * UserDetailsService 상속
  * MemberMapper 인터페이스를 이용하여 인증에 필요한 정보들을 얻어옴
    * 이때 의존성 주입 필요
  * Mapper에서 반환된 vo 객체를 UsersDetails 타입으로 변환 필요
    * User 클래스를 상속받은 클래스를 이용하여 구현
* 시큐리티 컨텍스트 설정
  * 커스텀 유저 서비스를 빈으로 등록 
  * authentication-provider 속성값을 이용하여 등록


## Chapter 34. JSP with 스프링 시큐리티
* 스프링 시큐리티에서 제공하는 태그 라이브러리 이용


## Chapter 35. 자동 로그인(remember-me)
### 스프링에서의 자동 로그인
* 자동 로그인
  * 로그인 한 후, 일정 기간 동안 세션이 끊긴 후 다시 접속 시 로그인이 필요하지 않는 기능
  * 브라우저의 쿠키 이용
* 스프링 시큐리티에서 처리하는 방식
  * 서버의 메모리 상 처리
    * 서버가 여러 개인 경우 데이터 공유가 불가능
  * 데이터베이스에서 처리
    * 서버가 여러 개인 경우 데이터 공유 가능
    * 로그아웃 시, 해당 정보가 테이블에서 삭제
* 시큐리티 컨텍스트의 security:remember-me 태그 이용하여 속성 지정
  * 쿠키 암호화를 키 값
  * 데이터베이스 이용 시 DataSource
  * 브라우저에 저장할 쿠키 이름
  * 로그인 시, 자동 로그인 체크박스의 name 값
  * 쿠키 유효 시간
* 데이터베이스를 이용한 자동 로그인
  * JDBC 처럼 스프링이 지정한 테이블을 생성하여 이용하는 방식
    * 단순히 로그인 유지에 필요한 정보만 저장하므로 해당 방식 사용
  * 직접 구현하는 방식

### 구현
* 테이블 생성
```
create table persistent_logins (
    username varchar(64) not null,
    series varchar(64) primary key,
    token varchar(64) not null,
    last_used timestamp not null
);
```
* 시큐리티 컨텍스트에 
  * 데이터 소스 설정
  * 로그아웃 시 쿠키 삭제를 위해 security:logout 의 delete-cookies 속성에 쿠키 등록
* 로그인 페이지에서 자동 로그인 체크박스 설정


## Chapter 37. 어노테이션을 이용한 스프링 시큐리티 설정
* 권한 설정을 위한 어노테이션
  * @Secured
    * 초기 버전부터 사용
    * 괄호 안에 문자열이나 문자열 배열로 권한 이름 설정
  * @PreAuthorize, @PostAuthorize
    * 괄호 안에 표현식 사용 가능
    * 최근에 많이 사용
* servlet-context.xml 설정
  * 스프링 시큐리티 어노테이션을 활성화하기 위한 설정
  * 시큐리티 컨텍스트가 아닌 스프링 MVC 컨텍스트에 추가 필요
* SampleController 컨트롤러에 예제 코드 추가