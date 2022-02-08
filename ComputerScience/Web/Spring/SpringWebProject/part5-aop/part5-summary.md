# AOP 와 트랜잭션

## 주요 이슈


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

