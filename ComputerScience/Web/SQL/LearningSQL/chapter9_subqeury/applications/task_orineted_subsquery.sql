/*
1. customer, address, city : 결과에서 보여주는 용도로만 사용
2. 그루핑 대상은 사실상 고객의 id 기준
=> payment를 이용하여 그룹핑 결과를 서브쿼리로 생성하여, 다른 정보를 출력하기 위해 inner join
*/
select c.first_name, c.last_name, ct.city, sum(p.amount) total_payments, count(*) total_rentals
from payment as p
inner join customer as c
	on p.customer_id = c.customer_id
inner join address as a
	on c.address_id = a.address_id
inner join city as ct
	on a.city_id = ct.city_id
group by c.first_name, c.last_name, ct.city;

/* 서브쿼리로 개선한 쿼리*/
select c.first_name, c.last_name, ct.city, subpay.total_payments, subpay.total_rentals
from 
(
	select customer_id, count(*) total_payments, sum(amount) total_rentals
    from payment
    group by customer_id
) as subpay
inner join customer as c
on subpay.customer_id = c.customer_id
inner join address as a
	on c.address_id = a.address_id
inner join city as ct
	on a.city_id = ct.city_id;