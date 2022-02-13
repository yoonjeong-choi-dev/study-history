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
  * 리다이렉션의 경우, response.redirected 속성을 이용하여 리다이렉션
  * TODO: Ajax 리다이렉션의 경우 플래시 메시지 전송 불가능

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