/*
possible_keys : 사용 가능한 인덱스 키들
key : 사용한 인덱스 키 이름
type : 스캔 방식 (range: 인덱스에서 범위 검색)
*/
explain
select customer_id, first_name, last_name
from customer
where first_name like 'S%' and last_name like 'P%';
    