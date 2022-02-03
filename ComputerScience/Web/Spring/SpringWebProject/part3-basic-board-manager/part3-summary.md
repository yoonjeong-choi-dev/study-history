# 기본적인 웹 게시물 관리 프로젝트

## 주요 이슈 정리
### myBatis 매핑 처리 이슈
* DB는 `sanke_case`, Java 프로퍼티는 `Camel Case` 로 설정되어 있음
  * myBatis는 테이블의 컬럼 이름으로 프로퍼티를 설정하기 때문에 VO 프로퍼티 설정이 제대로 안됨
  * VO 프로퍼티와 컬럼 이름의 소문자가 일치할 때 매핑하는 방식(by 리플렉션)
  * 컬럼 이름에 있는 언더바 때문에 null로 설정
* 다행히 날짜 관련 이슈(java.util.Date)은 org.apache.ibatis.type.DateTypeHandler 로 처리 가능
* 설정 파일 변경
  * myBatis 설정 파일 추가(mybatis-config.xml)
    * mapUnderscoreToCamelCase 값을 true 로 설정
  * root-context.xml 에서 myBatis 빈 등록 시, 설정 파일 추가 

### MockMVC 방식 테스트
* 서블릿 의존성 문제
  * 기존 방식에서는 서블릿 객체가 불필요 했음
  * MockMVC에서는 ServletContext 객체 필요
  * 테스트 과정에서 서블릿을 로드할 수 없는 문제 발생
* build.gradle 파일에서 testImplementation 에 서블릿 의존성 추가


## Chapter 7. 스프링 MVC 프로젝트 기본 구조
### 웹 프로젝트의 3 티어 방식
* 일반적인 웹 프로젝트의 3 티어 구성 요소
  * 화면 계층(Presentation) &leftrightarrow; 스프링 MVC 
  * 비즈니스 계층(Business) &leftrightarrow; 스프링 Core 및 spring-mybatis
  * 데이터 계층(Persistence) &leftrightarrow; mybatis 및 데이터베이스 
* 화면 계층
  * 화면에 보여주는 기술을 사용하는 영역
  * Servlet/JSP 나 스프링 MVC 담당
  * 스프링 MVC의 경우, 각 영역은 별도의 설정을 가지는 단위로 구성
    * root-context.xml : 서블릿 리스너 등록 시 필요한 설정
    * servlet-context.xml : DispatcherServlet 관련 설정
* 비즈니스 계층
  * 실제 요구 사항을 처리하기 위한 비즈니스 로직
  * 스프링 Core 영역은 보통 POJO 영역 i.e 스프링에 종속적이지 않음
  * POJO 객체 간의 연관 구조는 의존성 주입을 통해 완성
  * spring-mybatis 라이브러리를 이용하여 데이터 계층과 연결
* 데이터 계층
  * 데이터의 보관 및 사용에 대한 설계가 들어가는 계층
  * 보통 데이터베이스 이용
  * 경우에 따라 네트워크 호출이나 원격 호출 등을 이용하여 데이터 접근

### 웹 프로젝트의 디렉터리 구조
* 프로젝트를 구성하는 각각의 영역들은 독립적으로 설계
  * 영역 간 연결은 인터페이스를 이용
  * 인터페이스를 이용하여 영역에 대한 분리 가능
  * 독립적인 영역을 가지므로 유지 보수 용이
* 네이밍 규칙
  * xxxController
    * 스프링 MVC에서 동작하는 Controller 클래스
    * 모델 2의 페이지 컨트롤러의 역할로 서비스 객체를 이용하여 비즈니스 로직 수행
  * xxxService, xxxServiceImp
    * 비즈니스 영역에 해당하는 인터페이스 및 구현체
    * 컨트롤러에서는 인터페이스만을 이용하여 비즈니스 로직 수행
      * 구현체는 의존성 주입으로 컨트롤레에 주입
      * 서비스 로직에 대한 변경을 용이하게 하기 위하여 인터페이스 사용
  * xxxDAO, xxxRepository
    * 데이터 계층에 해당
    * 이 프로젝트에서는 DAO 대신 SQLMapper 사용
  * VO, DTO
    * 데이터를 담고 있는 객체로, 각 영역 사이에서 교환되는 데이터에 해당
    * VO(Value Object)
      * ReadOnly 목적이 강함
      * 보통 불변하게 설계하는 것이 정석
    * DTO(Data Transform Object)
      * 데이터 수집에 대한 용도가 강한 객체
      * 데이터 전달 및 직렬화에 이용
* 패키지 구조
  * 위에서 설명한 각 영역을 구분하여 패키지 분리
    * ex) Controller, Service를 별도의 패키지로 구성
  * 프로젝트가 커지게 되면, 비즈니스 단위로 패키지 분리
    * 분리된 패키지 내에 Controller, Service, DAO 등의 패키지를 다시 분리
    * 패키지가 많아지고 구성이 복잡해지는 단점

### 프로젝트 셋팅
* 기본적인 뼈대는 part1과 같은 방식으로 구성
  * 게시글 관련 테이블 생성  
    ```
    create table spring5web.board (
      id int auto_increment primary key,
      title varchar(200) not null,
      content text not null,
      writer varchar(50) not null,
      registered_date datetime default CURRENT_TIMESTAMP,
      modified_date datetime default CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
    ) engine = InnoDB default character set = utf8;
    ```
  * 더미 데이터 추가
    ```
    insert into spring5web.board (title, content, writer)
    values ('Test Title', 'This is a test data', 'test-yj');

    insert into spring5web.board (title, content, writer)
    values ('Another Title', 'This is a another test data', 'test-yj');
    ```
* 세팅 테스트 코드 작성
  * jdbc 드라이버 로드 테스트
  * DataSource 설정 테스트


## Chapter 8. 데이터/비즈니스 계층의 CRUD 구현
### 작업 순서
* 데이터베이스에서 테이블 설계 및 생성 후 작업
  * 각 데이터에 대한 CRUD 구현
  * 구현 테스트
* 데이터 계층의 작업 순서
  * 테이블의 컬럼 구조를 반형한 VO 클래스 작성
  * 쿼리를 실행하기 위한 Mapper 인터페이스 작성(myBatis)
  * 작성한 인터페이스 테스트
### 쿼리 작성
* BoardMapper 인터페이스 작성 및 테스트 코드 작성
* CRUD 관련 쿼리를 작성한 xml 추가
  * xml 작성 시, 부등호 사용이 불가능
  * <![CDATA[ {query} ]]> 형식으로 쿼리 작성
  * insertById 쿼리 작성 시
    * selectKey 쿼리를 oracle(교재)와 달리 mysql에 맞게 작성 필요
    * `select max(id)+1 from board`


## Chapter 9. 비즈니스 계층
### 구성
* 비즈니스 계층
  * 요구 사항을 반영한 계층
  * 표현 계층과 데이터 계층을 연결하는 역할
  * vs 데이터 계층
    * 데이터 계층은 데이터베이스를 기준으로 나눠서 설계
    * 비즈니스 계층은 다양한 데이터 계층을 동시에 사용하여 하나의 비즈니스 로직을 수행
* Service 객체
  * 비즈니스 영역에 존재하는 객체
  * Service 인터페이스와 구현체로 분리하여 구현
    * 계층 간 느슨한 결합 
    * 스프링 AOP의 프록시는 인터페이스 기반으로 동작하기 때문에 인터페이스 사용

### Service 구현체
* @Service 어노테이션 이용
  * 해당 클래스가 비즈니스 영역을 담당함을 의미
  * 스프링 빈 등록을 위해 root-context.xml 설정 추가
* 모델 데이터 처리를 위한 DAO 객체 주입
  * 현재는 Mapper 인터페이스 사용
  * 스프링 4.3 부터는 인자가 1개인 생성자의 경우 자동으로 주입 가능
  * 이전 버전은 @Autowired 를 이용하여 주입


## Chapter 10. 표현 계층의 CRUD 구현
* Controller 클래스 구현
  * 하나의 클래스에서 다양한 요청(URL)에 따라 분기 처리
  * 작성하기 전에 필요한 기능에 대한 URL, Method 및 필요한 파라미터 정의 필요
  * 비즈니스 계층에서 구현한 서비스 객체에 대한 의존성 주입
* 테스트 방식
  * 과거에는 뷰를 이용하여 테스트
    * 컨트롤러에서 반환하는 뷰를 통해 시각 적 테스트 
    * 뷰를 따로 구현해야 하며, 테스트 자동화가 어려움
    * WAS 실행이 반드시 필요
  * MockMVC 이용
    * 가짜로 url 요청을 만들어 Controller 테스트
    * @WebAppConfiguration 어노테이션을 이용하여 ServletContext 이용
  * junit 버전 차이
    * 버전 4 : @BeforeClass, @AfterClass, @Before, @After 
    * 버전 5 : @BeforeAll, @AfterAll, @BeforeEach, @AfterEach



## Chapter 11. 화면 처리
* 이전 챕터까지 백엔드 개발 및 테스트 완료
  * 모델 계층 및 비즈니스 계층 처리
  * 표현 계층(컨트롤러) 처리
  * 이후 생기는 문제는 화면과 관련된 문제
* 개발 환경
  * jsp 이용
  * 화면 스타일은 BootStrap 이용
    * SB Admin 관련 css/js 파일 추가 필요
    * webapp/resources 에 파일 추가
    * servlet-context.xml 에 리소스 매핑 url 추가
    * 인크루딩을 이용하여 스타일 필수 파일 적용
  * JSTL 추가
  * POST 폼 처리를 위한 폼 뷰 GET 요청을 컨트롤러에 추가
* 한글 처리를 위한 filter 추가
  * 필터는 web.xml 에서 설정
  * utf-8 인코딩 관련 필터는 스프링에서 제공
* 컨트롤러에서 전달한 플래시 메시지 출력
* 게시글 추가 및 수정 작업은 GET/POST 메서드를 이용하여 폼 페이지 응답/요청처리로 컨트롤러 메서드 분리