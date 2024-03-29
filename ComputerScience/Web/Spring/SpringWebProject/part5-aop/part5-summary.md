# AOP 와 트랜잭션

## 주요 이슈
* MyBatis 어노테이션 스캔 범위
  * 상황
    * chapter 19에서 간단한 트랜잭션 예시를 위해 모든 클래스를 com.yj.simpleTx 패키지에 넣었음
    * MyBatis Mapper 인터페이스와 서비스 인터페이스 및 구현체가 같은 범위
    * root-context.xml에서 서비스 컴포넌트 스캔 및 MyBatis 스캔 범위를 동일하게 설정
    * 테스트 코드에서 서버스 인터페이스에 대한 @Autowired 에러 (해당 빈이 2개로 나옴)
  * 원인
    * 동일 서비스 인터페이스에 대해서 2개의 인터페이스를 구현체 생성
      * 실제 서비스 구현체
      * MyBatis 프록시 객체
    * 테스트 코드에서 `DefaultListableBeanFactory` 객체를 의존성 주입하여 확인
  * 해결 방법
    1) MyBatis 스캔 범위를 좁히기 위해 mapper 패키지 분리
    2) 변수 이름을 `sampleTxService`(클래스 앞글자를 소문자로) 처리징
    3) 변수 타입을 구현체 클래스로 설정
  * 중복된 빈 객체가 2개 이상일 때, @Autowired 적용 순서
    1) @Qualifier와 같은 값을 갖는 빈 객체
    2) 변수명과 이름이 같은 빈 객체

## Chapter 18. AOP 패러다임
### 관심사
* 관심사(concern)
  * 개발 시 필요한 고민이나 염두에 두아야 할 사항
  * 핵심 로직은 아니지만 로직을 온전하게 만들어 주기 위해 필요한 고민들
* example
  * 파라미터 검증
  * 사용자 권한 확인
  * 예외 처리
* 관심사 분리
  * 과거에는 핵심 로직과 관심사가 한 코드에 반영
  * AOP가 추구하는 것은 관심사의 분리
    * 위의 관심사를 별도로 분리하여, 핵심 비즈니스 로직만 작성하는 것을 추구
    * AOP에서의 관심사는 중요 로직은 아니지만, 로직의 사전/사후 조건에 해당
  * 관심사와 비즈니스 로직을 분리하여 컴파일/런타임에 관심사 코드를 실행
* AOP에서의 개발 방식
  * 핵심 비즈니스 로직에만 근거해서 코드 작성
  * 해당 로직을 어떤 관심사들과 결합할 것인지 설정
  * 핵심 비즈니스 로직과 관심사 사이에는 명시적인 관계가 없는 독립적인 관계

### AOP 용어
* AOP 구성 요소
  * Target
  * Proxy
  * JoinPoint
  * PointCut
  * Aspect/Advice
* Target
  * 순수한 비즈니스 로직을 가지는 객체
  * Proxy를 통해 Target 객체의 메서드가 호출
  * Proxy를 통해 호출된 메서드가 JoinPoint
* Proxy
  * Target을 전체적으로 감싸고 있는 존재
  * 내부적으로 Target 메서드를 호출하지만, 중간에 필요한 관심사들으 거침
  * 대부분 스프링 기능을 이용하여 자동으로 생성되는 방식 이용(auto-proxy)
* JointCut
  * Target 객체가 가진 메서드
  * 외부에서의 호출은 Proxy 객체를 통해 Target 객체의 JoinPoint 메서드를 호출하는 방식
* PointCut
  * Target 객체의 어떤 메서드에 어떤 관심사를 결합할 것인지에 대한 결정
  * Target 객체는 PointCut에 의해서 자신에게 없는 기능이 추가되는 것
  * 관심사와 비즈니스 로직이 결합되는 지점을 결정
  * PointCut 설정 기준
    * execution : 메서드 기준
    * within : 특정 타입(클래스) 기준
    * this : 특정 인터페이스를 구현한 객체 기준
    * args : 메서드의 파라미터 기준
    * annoation : 적용된 어노테이션 기준
* Aspect/Advice
  * 관심사에 해당
  * Aspect는 관심사 자체를 의미하는 추상 명사
  * Advice는 Aspect를 구체화한(구현한) 코드
* 동작 위치에 따른 Advice 종류
  * Before Advice : JointPoint 호출 전에 실행
  * After Running Advice : 모든 실행이 정상적으로 종료된 후 실행
  * After Throwing Advice : 예외가 발생 한 뒤에 실행
  * After Advice : 정상/비정상 구분없이 종료 후 실행
  * Around Advice : 메서드 실행 자체를 제어할 수 있는 가장 강력한 Advice
  
### 예제 코드
* root-context.xml 설정 추가
  * `<aop:aspectj-autoproxy/>`
  * 스프링에서 자동으로 프록시 객체 생성
* com.yj.simpleAop 패키지
  * 간단한 AOP 예제
  * before 및 around advice 설정
  * 테스트 코드를 통해 서비스 객체를 감싸는 프록시 객체 확인 가능

## Chapter 19. 트랜잭션
### 트랜잭션
* 트랜잭션
  * 비즈니스에서 쪼개질 수 없는 하나의 단위 작업
  * 한 번에 이루어지는 작업의 단위
  * 데이터베이스 상에서 다수의 작업(쿼리)이 같은 묶음으로 이루어지는 상황에서 발생
  * 하나의 트랜잭션으로 처리해야하는 다수의 쿼리 중 하나가 잘못되면 이미 성공한 작업까지 원상 복구되어야 함
* 트랜잭션의 성격(ACID 원칙)
  * Atomicity(원자성)
    * 하나의 트랜잭션은 하나의 단위로 처리
    * 어떤 작업이 실패한 경우 트랜잭션을 구성하는 모든 작업이 원점으로 복구되어야 함
  * Consistency(일관성)
    * 트랜잭션 처리가 성공되면 모든 데이터는 일관성을 유지해야함
    * 트랜잭션으로 처리된 데이터와 일반 데이터 사이에는 차이 X
  * Isolation(격리)
    * 트랜잭션으로 처리되는 과정 사이에는 외부 영향 X
  * Durability(영속성)
    * 트랜잭션 처리가 성공되면 결과는 영속적으로 (데이터베이스에) 보관

### 데이터베이스 설계와 트랜잭션
* 정규화 작업
  * 데이터베이스의 저장 구조를 효율적으로 관리하기 위한 작업
  * 기본은 중복된 데이터의 제거를 통한 데이터 저장의 효율 향상
    * 데이터베이스를 구성하는 테이블의 개수 증가
    * 각 테이블의 필드 개수 감소
  * 정규화 작업을 통해 처리되지 않는 데이터 형식
    * 시간에 따라 쉽게 변경되는 데이터(나이)
    * 계산이 가능한 데이터
    * 누구에게나 정해진 값(특정일에 대한 요일)
  * 정규화의 장점
    * 데이터 중복의 감소로 인한 트랜잭션 발생 감소
  * 정규화의 단점
    * 쿼리의 복잡도 증가
    * 특정 데이터를 접근하기 위해 조인/서브쿼리 이용 필요
    * 성능상 이슈 발생
* 반정규화
  * 정규화의 단점을 해결하기 위한 방식
  * 정규화의 반대 과정으로 중복이나 계산이 가능한 데이터를 테이터베이스에 저장
  * 정규화의 결과로 발생하는 조인/서브쿼리의 사용을 줄이는 방식
  * 반정규화의 장점
    * 중복이나 계산의 결과를 미리 저장하여 빠르게 결과를 얻을 수 있음
    * 쿼리의 단순화
  * 반정규화의 단점
    * 여러 테이블에 중복된 데이터 존재
    * 중복된 데이터 관리를 위한 트랜잭션 관리 필수

### 예시 코드
* 트랜잭션 예시를 위한 테이블 생성
  * ```create table tx_test1 ( col1 varchar(500) )```
  * ```create tealbe tx_test2 ( col2 varchar(50) )```
* 트랜잭션 테스트를 위한 Mapper 및 서비스 구현
* 트랜잭션 설정
  * 트랜잭션이 필요한 부분에 @Transactional 어노테이션 설정
    * 메서드
    * 클래스
    * 인터페이스
  * 트랜잭션 관련 root-context.xml 설정
    * 트랜잭션을 관리하는 빈 객체 추가
    * 트랜잭션 어노테이션 스캔 설정
* 테스트 코드 작성


## Chapter 20. 댓글 수 트랜잭션 처리
* 게시판 테이블 수정
  * 반정규화를 통해 게시판 테이블에 해당 게시판의 전체 댓글 수 필드 추가
  * 테이블 변경 쿼리
    ```
    alter table board
    add (reply_count integer default 0);
    ```
  * 기존 데이터 댓글 수 처리
    ```
    update board
    set reply_count = (
      select count(*)
      from reply
      where board.id = reply.board_id
    );
    ```
* 게시판 관련 데이터 VO 및 Mapper 수정
  * 댓글 수 필드 수정 시, modified_date 필드 함께 수정 필요
    * 해당 필드는 `default CURRENT_TIMESTAMP ON UPDATE` 디폴트가 걸려있어서 수정 시 게시판 수정 시간이 변경
    * 댓글 자체는 게시판 수정과 관련이 없으므로 해당 필드는 예전처럼 유지 필요
* 댓글 서비스 구현체 수정
  * 게시판 Mapper 의존성 주입
  * 댓글 생성 및 삭제에서 게시판 테이블 데이터 수정