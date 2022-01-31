# Part 1. 스프링 개발 환경 구축

## 책과 다른 설정들
* gradle 버전 6 이상부터는 junit5로 테스트
  * build.gradle 파일 변경
  * 테스트 코드 변경
  * 테스트 실행 시 인텔리제이 설정
    * settings -> build, execution, deployment -> build tools -> gradle
    * build and run 탭에서 run test using을 IntelliJ로 변경
* 로그 관련
  * `SLF4J: Failed to load class "org.slf4j.impl.StaticLoggerBinder"` 에러 발생
  * slf4j-simple 의존성 추가

## Chapter 2. 스프링의 특징과 의존성 주입
### 스프링의 주요 특징
* POJO(Plain Old Java Object) 기반 구성
  * 스프링은 객체 간 관계를 구성할 때 별도의 API를 사용하지 않고 POJO의 구성만으로 개발 가능
  * 일반적인 Java 코드 만으로 개발 가능
  * 구성 요소가 되는 Java 클래스들이 특정 라이브러리나 컨테이너 기술에 독립적
* 의존성 주입(DI, Dependency Injection)
  * 의존성
    * 하나의 객체가 다른 객체 없이 기능을 수행할 수 없는 상황
    * 하나의 객체가 다른 객체 상태에 영향을 받는 것
  * 주입
    * 외부에서 의존성이 있는 객체를 밀어 넣는 것
    * 객체가 자신이 필요한 객체를 얻는 행위가 능동적인지 수동적인지에 대한 차이
      * 능동적 : 필요한 객체를 `new` 키워드를 통해 자신이 생성
      * 수동적 : 필요한 객체를 외부에서 생성자나 세터를 통해 주입
  * 의존성 주입의 장점
    * 주입받는 객체는 자신이 필요한 객체가 정확히 어떤 형태인지 몰라도 된다
    * 어떤 객체에 의존하든지 자신의 역할은 변하지 않음
  * 스프링에서의 의존성 주입 방식
    * ApplicationContext
      * 프로그램에 필요한 객체 생성 및 관리
      * 필요한 객체를 주입
      * 이때 ApplicationContext가 관리하는 객체들을 **빈(Bean)** 이라고 부름
    * 사용자는 객체들을 분리하여 생성하고, 객체들을  엮는(wiring) 방식으로 개발
    * 객체 간 의존 관계를 처리하는 방식
      * xml 설정
      * 어노테이션 이용
      * Java 설정 방식
* AOP
  * AOP의 필요성
    * 좋은 개발 환경에서는 개발자가 비즈니스 로직에만 집중이 가능
    * 비즈니스 로직 의외의 반복적인 코드의 제거가 필요
  * 횡단 관심사(cross concern)
    * 대부분의 시스템이 공통적으로 필요한 기능
      * 보안
      * 로그
      * 트랜잭션
    * 이러한 공통 기능들은 비즈니스 로직은 아니지만, 반드시 처리가 필요한 기능들
    * 공통 기능들을 비즈니스 로직과 분리하여 모듈로 관리하는 패러다임이 AOP
  * 스프링에서는 AspectJ 문법을 이용하여 AOP 지원
    * 개발자는 핵심 비즈니스 로직에만 집중 가능
    * 관심사들의 변경이 있어도 비즈니스 로직에 대한 코드는 수정을 최소화 가능
    * 관심사 자체에 대한 유지 보수 용이
* 트랜잭션
  * 데이터베이스 관련 개발 시, 트랜잭션 관리는 필수
  * 스프링에서는 트랜잭션 관리를 어노테이션이나 xml 설정 파일로 설정

### 코드 정보
* spring web mvc 설정이 제대로 되었는지 확인하는 SampleController 및 뷰 파일
* 간단한 DI 예시(com.yj.di) 및 테스트 코드
  * 생성자는 묵시적으로 의존성 주입(Hotel)
  * 세터는 명시적으로 @autowired 어노테이션 이용(Restaurant)


## Chapter 3. 데이터베이스 연동
### MySql 설정
* 책과 다르게 MySQL 사용
  * MySQL 용 jdbc 드라이버를 gradle에 추가
  * 데이터베이스 설정
  ```
  create database spring5web default character set utf8;
  set global validate_password.policy=LOW;
  CREATE USER 'spring5webuser'@'localhost' IDENTIFIED BY 'spring5webuser';
  grant all privileges on spring5web.* to 'spring5webuser'@'localhost';
  flush privileges;
  ```
  * 간단한 연결 테스트(com.yj.persistence.JDBCTest) 코드 추가
* 데이터 풀 HikariCP 설정
  * 간단한 연결 테스트 코드 추가(com.yj.persistence.DataSourceTest)
  * root-context.xml 에서 데이터베이스 드라이버 및 연결 정보 설정


## Chapter 4. MyBatis 연동
* SQL 매핑 프레임워크 MyBatis 설정
  * root-context.xml 에 sqlSessionFactory 설정 및 어노테이션 스캔 범위 설정
  * 간단한 연결 테스트 코드 추가(com.yj.persistence.MyBatisTest)
* Mapper 인터페이스 작성을 통한 sql 쿼리문 작성
  * 어노테이션 및 xml 파일을 이용한 쿼리 예시 
  * 인터페이스만 작성하여도, 프레임워크가 해당 쿼리를 실행해주는 프록시 객체 생성
  * 간단한 테스트 코드를 통한 Mapper 객체 및 결과 출력(com.yj.mapper.TimeMapperTest)
* 쿼리 로깅을 위한 log4jdbc-log4j2 라이브러리 추가
  * 로깅 설정 파일 (log4jdbc~) 추가
  * DataSource 설정에서 jdbc driver 및 url 변경