/*
exist : 서브 쿼리가 하나 이상의 행을 반환했는지 여부만 확인 
=> 서브 쿼리는 단순히 행을 출력하기만 하면 됨
=> select * 나 select 1 을 사용하는 것이 규칙
*/
select c.first_name, c.last_name
from customer as c
where exists (
	select 1 from rental as r
    where r.customer_id = c.customer_id
    and date(r.rental_date) < '2005-05-25'
);