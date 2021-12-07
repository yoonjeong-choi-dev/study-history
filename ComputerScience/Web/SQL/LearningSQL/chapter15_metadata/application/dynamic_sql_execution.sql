/* 서버에 전송할 쿼리 문자열 정의 */
set @qry = 'select customer_id, first_name, last_name from customer where customer_id = ?';

/* 준비 구문 : 구문 분석, 검사, 최적화를 위해 DB 엔진에 쿼리 제출*/
prepare dynsql1 from @qry;

/* 변수 설정 */
set @custid = 9;

/* 쿼리 실행 */
execute dynsql1 using @custid;

/* 해당 쿼리 관련 리소스 해제*/
deallocate prepare dynsql1;