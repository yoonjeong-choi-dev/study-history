# Spring MVC 설정

## Chapter 5. 스프링 MVC의 기본 구조
### 스프링 MVC 설정 영역(WEB-INF/)
* 프로그램 실행 시 필요한 xml 파일
  * 톰캣 설정
    * web.xml
  * 스프링 설정
    * root-context.xml
    * servlet-context.xml
* web.xml
  * 톰캣과 같은 WAS 설정
  * 서블릿 설정
  * Context Listener 등록
    * root-context.xml 파일을 이용하여 컨텍스트 초기화 변수들을 등록
      * root-context.xml 파일을 처리하면서 파일에 있는 빈들을 등록
      * 등록된 빈들은 스프링의 컨텍스트 안에 생성되고 의존성이 처리됨
    * javax.servlet.ServletContextListener 구현체를 등록
      * 웹 애플리케이션이 실행 및 종료 시 로직들을 구현
      * 웹 애플리케이션 실행 중에 전체적으로 필요한 공유 객체들을 준비
      * 주로 데이터베이스, DAO 등 전반적으로 필요한 객체들을 빈으로 등록0
  * Dispatcher Selvet 등록
    * 역할 : 포론트 컨트롤러 in Front-Controller Pattern
      * 클라이언트의 요청을 받음
      * 요청을 처리할 컨트롤러를 정하여 요청 전달
      * 컨트롤러의 결과를 클라이언트에게 전달
    * servlet-context.xml 파일로 설정
    
### 모델 2와 스프링 MVC
* Servlet/JSP 개발
  * 각 요청 처리는 GenericServlet 를 상속받은 객체에서 한다
    * 각 처리에 대한 메서드는 ServletRequest/ServletResponse 객체를 요청/응답 인자로 받음
    * 각 요청에 대한 url과 구현된 서블릿 객체를 web.xml에서 연결하여 프로그램 개발
  * 스프링 MVC는 비즈니스 로직과 Servlet/JSP 사이에 하나의 계층을 추가한 구조
    * 비즈니스 로직을 처리하는 쪽에서는 Servlet API 에 대한 존재를 모른다
    * 스프링 내부적으로는 서블릿 사용
* 서블릿 프로그래밍에서의 모델2 MVC 구조
  * 컨트롤러
    * 사용자의 요청 처리에 대한 흐름 제어
      * 비즈니스 로직을 처리하는 모델을 적절히 호출하여 요청 처리
      * 모델을 이용하여 요청을 처리하면 응답을 위한 데이터를 뷰에게 전달
    * 서블릿 객체를 이용
  * 모델
    * 특정 비즈니스 로직을 처리하는 객체
    * 서블릿과 상관없는 순수한 데이터 처리 로직
  * 뷰
    * 모델에서 처리한 데이터를 컨트롤러에서 전달
    * 전달받은 데이터를 이용하여 사용자에게 적절한 뷰 제공
* 스프링에서의 모델 2 MVC 구성 요소
  * 기존 MVC에서 Front Controller 패턴을 적용하여 컨트롤러의 역할을 2가지로 분리
    * 요청에 대한 흐름을 제어하는 Front Controller
    * 특정 요청에 대한 처리를 담당하는 Page Controller
  * Front Controller
    * Dispatcher Selvet 객체
    * HandlerMapping 객체를 이용하여 처리를 담당하는 Page Controller 찾음
  * Page Controller
    * 특정 요청에 대한 처리를 담당
    * 요청을 처리한 뒤 결과를 반환
    * 응답 결과를 Dispatcher Selvet 객체가 요구하는 형식으로 반환
  * HandlerMapping
    * Front Controller와 Page Controller 사이의 매핑 정보
    * Front Controller는 HandlerMapping을 이용하여 Page Controller 객체를 연결
  * HandlerAdapter
    * Front Controller와 Page Controller 사이의 데이터 변환 담당
    * Page Controller에서 필요한 데이터를 요청 데이터에서 변환
    * Page Controller의 결과값을 Front Controller에서 요구하는 형식으로 변환
  * ViewResolver
    * Page Controller 처리 결과를 보여줄 뷰를 결정
    * Page Controller는 다양한 결과를 반환
    * 비즈니스 로직과 응답 사이의 데이터 변환 역할 i.e 처리 결과에 대한 다양한 뷰 제공
  * View
    * Page Controller 처리 결과 화면 생성
    * 다양한 형식으로 응답 결과를 클라이언트에게 전송


## Chapter 6. 스프링 MVC Controller
### 스프링 MVC Controller 특징
* 서블릿 웹 프로그래밍에서 필수였던 HttpServletRequest 및 HttpServletResponse 인자 사용없이 구현
* HTTP Method에 대한 전송 방식에 대한 처리를 어노테이션으로 처리
* 상속/인터페이스 구현 방식 대신 어노테이션을 이용하여 요청 처리에 대한 설정 가능
* 다른 프레임워크와 달리 스프링 MVC는 어노테이션을 중심으로 구성
  * @Controller 어노테이션이 설정된 클래스들에 대해서 ServletContext가 객체 생성
* 간단한 컨트롤러(SimpleController)
  * @RequestMapping 어노테이션을 이용하여 처리할 요청과 비즈니스 로직(메서드) 연결
    * @GetMapping 및 @PostMapping 으로 HTTP 메서드 지정 가
  * @RequestParam 어노테이션을 이용하여 요청에 있는 파라미터의 키값 설정 가능
    * 해당 파라미터 키에 대한 데이터를 메서드 인자로 받음
  * @ResponseBody 와 VO 반환형을 이용하여 json 응답
    * jackson-databind 라이브러리를 이용하여 응답 MIME 타입 변
* 파리미터 변환(BindingController)
  * @InitBinder 어노테이션을 이용하여 요청 데이터를 적잘한 VO 변환 가능
    * WebDataBinder를 인자로 받음
    * 바인더 객체를 통해 커스텀 에디터를 등록
* 파일업로드(UploadController)
  * commons-fileupload 라이브러리 추가 및 multipartResolver 빈 등록
  * MultipartFile 객체를 이용하여 파일에 대한 정보(이름, 크기, 타입, 데이터) 접근 가능

### 예외 처리
* AOP를 이용한 에러 처리 방식
  * 예외를 처리하는 Advice를 구현(CommonExceptionAdvice) 
  * @ControllerAdvice : 객체가 공통 관심사임을 표시
  * @ExceptionHandler : 속성으로 예외 클래스를 지정하여 특정 예외에 대한 처리 담당
* 서버 에러(500) 및 클라이언트 에러(404) 구분 필요
  * 서버 에러는 @ExceptionHandler 의 속성으로 예외 클래스 설정 이용
  * 클라이언트 에러는 NoHandlerFoundException 예외 클래스로 설정
    * WAS 설정 파일(web.xml) 에서 Dispatcher Selvet 객체 설정 변경 필요
    * throwExceptionIfNoHandlerFound 값을 true로 설정