# 프로젝트 첨부파일

## 주요 이슈
* MySQL 첨부파일 트랜잭션 처리 이슈(insertWithId)
  * 교재처럼 게시글 데이터를 넣기 전에 `<selectKey>` 사용 시, 외래키 참조 에러 발생
  * MySQL 쿼리를 이용하여 데이터를 넣은 후, 해당 데이터의 id를 가져옴
  * ```
    <selectKey keyProperty="id" resultType="long">
            SELECT LAST_INSERT_ID()
        </selectKey>
    ```
* POST Ajax 처리
  * 등록 시, 숫자 관련 문제로 form 요청 대신 ajax 처리
  * ~~리다이렉션의 경우, response.redirected 속성을 이용하여 리다이렉션~~
  * ~~TODO: Ajax 리다이렉션의 경우 플래시 메시지 전송 불가능~~
  * input 태그를 동적으로 생성하고, 숫자의 경우 타입을 number 로 설정

## Chapter 25. 프롲게트의 첨부 파일 등록
### 첨부 파일 정보 추가
* 테이블 설계
  ```
  create table attach_file (
    uuid            varchar(100) not null,
    upload_path     varchar(200) not null,
    file_name       varchar(100) not null,
    is_image        tinyint default 1,
    board_id        int not null,
    primary key (uuid),
    constraint fk_file_board_id foreign key (board_id) references board (id) on delete restrict on update cascade
  ) engine = InnoDB default character set = utf8;
  ```
  * 게시글과 첨부 파일 데이터 관계
    * 1:N 관계
    * 게시글의 id를 외래키로 설정
* VO 설계
  * 첨부 파일 테이블에 대응하는 BoardAttachFileVO
  * BoardVO에 첨부파일 VO 리스트 추가
* DTO 설계
  * Mapper 인터페이스 추가
  * xml 파일에 쿼리 추가

### 첨부 파일 등록
* 뷰 설계
  * 게시글 등록 페이지에 첨부 파일 관련 레이아웃 추가
  * ajax 호출을 이용하여 첨부 파일 데이터도 함께 전달
  * 이전 프로젝트(part6-1)의 uploadAjax.jsp 코드와 유사
  * 등록 시, 숫자 관련 문제로 form 요청 대신 ajax 처리
* UploadController
  * 이전 프로젝트에서 만들었던 컨트롤러
  * 데이터베이스와는 무관하게 파일을 서버에 저장하는 역할
  * 응답 및 요청 데이터를 위한 DTO 추가
    * UploadFileDTO
    * DeleteFileDTO


## Chapter 26. 게시물 조회와 첨부파일
### 게시물 조회 시, 첨부 파일 데이터를 가져오는 방법
* join 이용
  * 게시물 테이블과 첨부 파일 테이블을 join 하여 데이터 처리
  * 데이터베이스에 한 번만 쿼리를 하기 때문에 성능이 좋음
  * 전통적인 방식
* 첨부파일은 ajax 호출을 이용하여 처리
  * 쿼리를 2번해야 하는 부담
  * 뷰에서 처리해야 하는 로직 추가 필요
  * 예제에서 사용하는 방식

### 첨부 파일 조회
* 게시물 서비스에 특정 게시글에 대한 첨부 파일 정보를 가져오는 기능 추가
* 뷰 처리
  * get.jsp 페이지에서 게시글 id 이용하여 첨부 파일 데이터 fetch
  * 각 파일 데이터에 대한 레이아웃 생성
    * 이미지는 클릭 시 원본 이미지
    * 일반 파일은 클릭 시 저장


## Chapter 27. 게시물 삭제와 첨부파일
### 구현
* 게시글 삭제 시 첨부 파일도 같이 삭제
  * 데이터베이스에서 두 테이블에 대한 데이터 삭제 필요
  * 첨부 파일을 스토리지에서도 삭제 필요
* 데이터베이스 처리
  * 첨부파일 Mapper 에 특정 게시글 id에 해당하는 모든 데이터 삭제 메서드 추가
  * 게시판 서비스에서 게시판 삭제 시, 첨부 파일 mapper 호출(트랜잭션 처리 필요)
* BoardController 삭제 메서드 수정
  * 게시글 삭제 프로세스
    * 삭제해야할 첨부 파일 데이터 준비
    * 데이터베이스 삭제 처리
    * 데이터베이스 처리 완료 후, 파일 삭제
  * UploadController 수정
    * 로컬 스토리지 파일 경로를 반환하는 static getter 메서드 추가

### 추가 구현 기능
* 댓글이 있는 경우 게시글 삭제가 불가능한 현상
  * 댓글 테이블이 게시글 삭제 테이블의 키를 외래키로 참조
  * 댓글 삭제 이전에 게시글 삭제 시 쿼리 에러 발생
* 첨부 파일 삭제와 같은 로직으로 변경 필요
  * ReplyMapper 특정 게시글에 대한 댓글 데이터 삭제 메서드 추가 
  * BoardService에 ReplyMapper 의존성 주입


## Chapter 28. 게시물 수정과 첨부파일
### 구현
* 뷰 modify.jsp 수정
  * 처음에 첨부파일을 가져오는 부분은 get.jsp와 동일
  * 첨부파일 등록/삭제 로직은 register.jsp과 비슷
    * 삭제의 경우, 화면 상에서만 삭제.
    * 실제 파일 삭제는 컨트롤러에서 처리
* 서비스 변경
  * 첨부파일의 경우, 우선 모두 데이터베이스에서 삭제
  * 요청으로 온 첨부 파일을 대상으로 다시 데이터베이스에 등록
  * 스토리지의 파일처리는 다음 챕터에서 처리


## Chapter 29. 잘못 업로드된 파일 삭제
* 파일 업로드 Ajax 처리의 문제점
  * 첨부파일을 등록하는 시점에서 스토리지에 해당 파일을 저장하는 방식
  * 게시글 등록/수정이 정상적으로 이루어지지 않는 상태에서는 스토리지에 쓸모없는 파일이 계속 저장
    * 첨부파일만 등록하고 게시글 등록 버튼을 누르지 않은 상황
    * 수정 시, 첨부파일 관련 등록/삭제만하고 수정 버튼을 누르지 않는 상황
* 데이터베이스와 로컬 스토리지 사이의 데이터 불일치를 처리해야 함
  * 오늘 이전 날짜들에 대해서만 처리 필요
  * 오늘 날짜에 해당하는 디렉터리에는 현재 등록/수정 중인 데이터가 있을 가능성이 있음
  * 주기적인 처리(cron)를 위해 Spring-Batch, Quartz 라이브러리를 이용
    * Spring-Batch는 많은 양의 데이터에 대해서 유용하지만 설정 복잡
    * gradle 파일에 quartz 라이브러리 추가
* Quartz 라이브러리를 이용한 cron 설정
  * task 패키지에 파일 체크를 위한 클래스 추가
  * root-context.xml
    * 태크스 어노테이션을 사용하기 위해 task:annotation-driven 추가
    * task 패키지 컴포넌트 스캔 추가
  * 이전 날짜의 첨부파일 데이터를 가져오는 쿼리를 BoardAttachFileMapper 에 추가
  * 처리 순서
    * 어제 사용된 파일 목록을 데이터베이스에서 가져옴
    * 어제에 해당하는 디렉터리에서 데이터베이스에 없는 파일 목록 구함
    * 위에서 구한 파일 목록 삭제