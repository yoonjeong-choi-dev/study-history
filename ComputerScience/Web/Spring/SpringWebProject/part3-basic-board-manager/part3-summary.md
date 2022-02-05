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
    * 인크루딩을 이용하여 스타일 필수 파일 적용트
  * JSTL 추가
  * POST 폼 처리를 위한 폼 뷰 GET 요청을 컨트롤러에 추가
* 한글 처리를 위한 filter 추가
  * 필터는 web.xml 에서 설정
  * utf-8 인코딩 관련 필터는 스프링에서 제공
* 컨트롤러에서 전달한 플래시 메시지 출력
* 게시글 추가 및 수정 작업은 GET/POST 메서드를 이용하여 폼 페이지 응답/요청처리로 컨트롤러 메서드 분리


## Chapter 12. 페이징 처리
### 페이징 처리
* 데이터베이스를 이용한 프로그래밍에서 신경써야 하는 부분
  * 빠르게 처리(쿼리 속도)
  * 필요한 양만큼만 데이터 가져오기
* 페이징을 하는 이유
  * 요청에 대해서 최소한의 데이터를 가져와 빠르게 응답하기 위해서
* 페이징 처리 방식
  * 번호를 이용한 페이징 처리
    * 웹 개발 초기부터 이어오던 방식
    * 특정 페이지에 있는 특정 개수의 데이터를 응답하는 방식
  * 무한 스크롤, 더보기
    * Ajax 와 웹 앱 등장 이후 나오는 방식
* Oracle vs MySQL
  * 오라클은 MySQL에 비해 페이지 처리에 추가적인 작업 필요
    * MySQL은 limit ?, ? 형태로 처리
  * (TODO) MySQL 페이징 쿼리 최적화 리서치

### 오라클의 페이징 처리
* 실행 계획(execution plan)
  * SQL을 데이터베이스에서 어떻게 처리할 것인지에 대한 계획
  * SQL 쿼리가 데이터베이스에 전달되면, 데이터베이스는 비용이 가장 낮다고 판단되는 실행 계획을 세움
  * 실행 계획을 세우는 주체는 데이터베이스
    * 데이터의 양이나 제약 조건 등의 여러 상황에 따라 실행 계획이 달라짐 
* 데이터베이스의 SQL 처리 방식
  * SQL 파싱 단계
    * SQL 구문 오류 확인
    * 실행해야 하는 대상(테이블, 제약 조건, 권한) 검사
  * SQL 최적화 단계
    * SQL 구문을 실행하는데 필요한 비용 계산
    * 계산된 비용을 기반으로 실행 계획을 세움
  * SQL 실행 단계
    * 실행 계획을 실행하는 단계
    * 데이터의 조작에 대한 작업
* SQL 처리 방식 분석
  * 쿼리 튜닝 시 필요한 단계
  * MySQL의 경우, explain 키워드 사용
* 인덱스
  * 정렬 관련 문제에 대한 일반적인 해결책
  * 테이블의 특정 열들에 대한 인덱스 지정
    * 해당 인덱스를 기준으로 특정 테이블이 내부적으로 생성(인덱스 테이블)
    * 인덱스 테이블의 가장 큰 특징은 인덱스를 생성한 열들에 대해서 정렬이 되어 있음
  * 스캔(scan) : 정렬이 되어 있는 인덱스 테이블을 통해 특정 데이터를 찾는 행위
  * 정렬이 필요한 상황에서 우선적으로 생각하는 것이 테이블의 인덱스 설정
* 힌트(hint)
  * 데이터베이스가 실행 계획을 만드는데 참고할 수 있는 정보
  * 사용자는 힌트를 통해 데이터베이스의 실행 계획에 관여 가능
  * 영향을 줄 뿐, 힌트대로 실행 계획을 결정하지는 않음
* ROWNUM
  * 오라클에서 페이지 처리를 위해 필요한 키워드
  * 테이블에서 데이터를 추출한 후 처리되는 변수
    * 테이블에서 가져온 데이터를 이용하여 번호를 매기는 방식
    * 쿼리의 결과 테이블에 대한 번호
  * 쿼리 결과에서의 순서에만 영향을 준다
    * 쿼리의 중간 과정에 대해서는 영향을 주지 못함
    * 페이징을 하기 위해서는 인라인 뷰가 필요
* 인라인 뷰(in-line view)
  * ROWNUM을 사용하기 위해서는 쿼리 결과 자체에 대한 변경이 필요
  * 쿼리 결과를 변경하기 위해 인라인 뷰 사용
  * FROM 절 안에서 사용되는 서브 쿼리
    * 복잡한 select 쿼리에 대한 뷰(view)
    * 뷰(특정 쿼리 결과)를 하나의 테이블로 생각하여 쿼리문 작성
  * 외부에서는 select 쿼리를 하나의 테이블로 사용 가능
 
### MySQL 페이징 처리
* 방법 1
  * `select * from board order by id desc limit {데이터 개수} offset {시작행}`
  * limit & offset 
    * limit { 데이터 개수 }
    * offset { 시작 행 } (0부터 시작)
  * offset 사용 시, 시작 행 + 데이터 개수의 열을 읽기 때문에 성능 상 문제가 있음
    * offset은 쿼리 결과를 만들기 전에 건너뛰는 레코드 갯수
    * offset 이전의 데이터를 모두 조회하는 방식
* 방법 2
  * `select * from board order by id desc limit {시작행}, {데이터 개수}`
  * limit 키워드 하나로 오라클의 `rownum` 페이지네이션 기능 구현 가능
  * 인덱스 이용시, 시작행으로의 접근이 빠름
    * offset 자체는 인덱스를 사용하지 않음
    * 인덱스를 사용하지 않는 쿼리의 경우 방법 1 및 2가 동일
  * 교재의 쿼리와 동일한 성능
* 방법 3
  ```
  SELECT *
  FROM
  (
    SELECT @rownum:=@rownum+1 as rnum, A.*
    FROM board as A, (SELECT @ROWNUM := 0) R
    WHERE 1=1 
    order by id desc
  ) list
  WHERE rnum >= 12000 AND rnum <12010 order by rental_id desc
  ```
  * 오라클의 `rownum` 개념을 이용하는 방식
  * 서브쿼리를 이용하여 해당 개념이 없는 개선 가능(방법4)
* 방법 4
  ```
  SELECT *
  FROM
  (
    SELECT * from board
    order by id desc
    limit 10000, 20
  ) list
  ```
  * 방법 2에서의 개선
  * 인덱싱을 이용한 방법 2에서 발생하는 문제
    * `Row lookup` : 인덱스를 가르키는 열을 접근하여 가져오는 행위
    * 인덱스 테이블과 실제 테이블은 데이터베이스 내 메모리 주소를 가리키는 `ROWID`로 연결
  * TODO : Late row lookup


## Chapter 13. MyBatis를 이용한 페이징 처리
### 페이징 처리
* 페이징에 대한 VO 클래스 정의
  * PageCriteria 클래스
    * 현재 페이지 : 1부터 시작
    * 한 페이지에 있는 컨텐츠 개수
  * MySQL의 limit 키워드를 위해 시작 인덱스 프로퍼티 추가
* 페이징 기능 추가
  * Mapper 인터페이스 및 xml 쿼리 추가
  * 서비스 인터페이스 및 구현체에 메서드 추가
  * 컨트롤러의 `GET /board/list` 로직 변경
  * 각 영역에 대한 테스트 코드 추가

## Chapter 14. 페이징 처리 뷰
* `GET /board/list` 에 반영 필요
  * `/board/list/jsp` 코드 변경 필요
  * 목록 페이지에서 조회/수정/삭제 페이지 번호가 계속 유지되어야 함
* 목록 페이지에서 필요한 정보들
  * 현재 페이지 번호
  * 이전과 다음으로 이동 가능한 링크 표시 여부
  * 현재 화면에 보여주어야 할 페이지들의 시작 및 끝 번호
* 보여주어야 할 끝 페이지 및 시작 페이지 번호
  * 페이지 번호를 `nPage` 만큼 사용자에게 보여줘야한다고 가정
  * 현재 보여줘야할 시작 페이지 번호(startPage) = 끝 페이지 번호(endPage) - `nPage` + 1
    * 끝 페이지 번호는 전체 데이터 수의 종속
    * 끝 페이지 번호 = `Math.ceil(현재 페이지 번호 / nPage) * nPage`
    * 실제 보여줘야할 끝 번호 페이지(endPage)의 경우, 마지막 페이지에서 문제 발생
      * 실제 페이지 개수(realEndPage) = `Math.ceil(total / 한 페이지에 보여지는 컨텐츠 개수)`
      * 실제 보여줘야할 끝 번호 페이지 = `endPage > realEndPage ? realEndPage : endPage`
  * 시작 페이지 번호보다 끝 페이지 번호를 계산하는 것이 훨씬 깔끔
  * 이전과 다음으로 이동할 때 필요한 페이지 번호
    * 이전으로 이동하는 페이지 번호 = `startPage -1 > 0 ? startPage -1 : 1`
    * 다음으로 이동하는 페이지 번호 = `endPage < realEndPage ? endPage + 1 : realEndPage`
  * 결론 : 목록 페이지에 필요한 정보를 저장하는 VO 클래스 정의(PageDTO)
* 브라우저의 출력을 변경하기 위해 컨트롤러 변경
  * PageController list 메서드 변경
* list.jsp 변경
  * 페이징 버튼 레이아웃 추가
  * a 태그 관련
    * form 태그를 이용하여 정보 저장
    * 자바스크립트를 이용하여 a 태그 링크 동적 생성
  * get 및 update 폼에서 리스트 이동 시 페이지 유지 필요
    * form 태그를 이용하여 해당 페이지 url에 페이지 정보 추가
    * 컨트롤러에 PageCriteria 파라미터 추가 및 정보 전달
    * @ModelAttribute 어노테이션을 이용하여 페이지 정보를 인자로 받아 Model 객체에 넘긴다
  * update 폼 개선
    * 폼 태그 방식으로 리스트에 GET하기 때문에 폼에 있는 모든 정보(제목, 내용, 작성자 등)이 모두 url에 저장
    * 리스트 페이지 이동시, 필요한 정보를 뺀 폼 태그 하위 input 태그 삭제 후 실행
  * update 및 delete post 요청 시, 페이지 파라미터 처리 필요
    * @ModelAttribute 어노테이션을 이용하여 페이지 정보를 인자로 받아온다
    * 리다이렉션 설정에 해당 정보들을 설정
* BoardMapper에 페이지 전체 개수 구하는 기능 추가
  * 쿼리 작성 시 인덱스 사용을 위해 where 절 추가
  * 페이지 정보에 대한 검증 추가(Controller)


## Chapter 15. 검색 처리
### 검색 기능
* 클라이언트에서의 검색 조건
  * select 태그 이용
    * 단일 항목 검색에 사용
    * 보통 일반 사용자에게 제공하는 용도
  * checkbox 태그 이용
    * 다중 항목 검색에 사용
    * 관리자용이나 다양한 검색 기능을 제공할 때 사용
* 검색 기능을 위한 쿼리
  * 단일 항목 쿼리는 `like` 키워드 사용
  * 다중 항목의 경우 `like` 키워드와 함께 조건 연산자(`and`, `or`) 사용
* MyBatis 동적 SQL
  * 다중 항목 쿼리의 문제
    * 검색의 대상이 되는 항목들이 동적인 데이터
    * 검색 조건이 변경되면 SQL 역시 변경되는 문제 발생
  * MYBatis 동적 SQL을 이용하여 해결
    * 동적 SQL 작성을 위한 태그 제공
    * if, choose(when, otherwise), trim(where, set), foreach
    * 사용 방식은 JSTL과 비슷

### 검색 기능 구현
* PageCriteria 변경
  * 검색 조건과 검색에 사용하는 키워드 정보 저장
* 변경된 PageCriteria 에 맞는 쿼리 작성
  * sql 태그를 이용하여 SQL 일부 저장하는 형태 
  * 쿼리 테스트 코드 추가(BoardMapperTest)
* 뷰 구현 시 주의점
  * 검색 조건 및 키워드는 url을 통해 전송 : 해당 정보들을  
    * 검색 버튼 클릭 시, 검색 결과에 대해 1페이지로 이동 : 
  * 한글의 경우 url encoding 문제 발생 가능성 존재 : 인코딩 필터를 통해 정상적으로 동작
* `<c:out>` 태그 사용 이유
  * 검색어는 쿼리에 직접 넣는 방식으로 실행
  * 검색어에 명령어가 들어가 있는 경우 보안에 취약
  * 문자열 그자체로 인식하도록 만들어준다
* POST 리다이렉트 수정
  * 수정 및 삭제 POST는 리다이렉트로 동작
  * 리다이렉트 시, 검색 관련 정보를 포함 시켜야 한다
  * 리다이렉트(응답) 객체에 해당 정보 추가
  * update 폼 개선
    * 폼 태그 방식으로 리스트에 GET하기 때문에 폼에 있는 모든 정보(제목, 내용, 작성자 등)이 모두 url에 저장
    * 리스트 페이지 이동시, 필요한 정보를 뺀 폼 태그 하위 input 태그 삭제 후 실행
* 빌더 패턴을 이용한 리다이렉션 처리
  * 리다이렉션 이용시, 특정 데이터를 함께 전송해야 하는 상황
    * POST 리다이렉션
    * 리다이렉션 객체에 정보 등록 필요(addAttribute)
    * 해당 정보들은 PageCriteria 객체에 있는 정보들
  * UriComponentsBuilder 클래스를 이용하여 PageCriteria 객체 정보를 Uri 형태로 변형하여 코드 개선
* 검색 페이징 구현
  * 전체 데이터를 구하는 `BoardSerivce.getTotalCount` 메서드에 현재 검색 정보 PageCriteria 객체 인자로 넣는다
  * DAO, Service, Controller 변경