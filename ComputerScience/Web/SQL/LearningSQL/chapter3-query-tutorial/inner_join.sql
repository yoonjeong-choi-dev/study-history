select c.first_name, c.last_name, time(r.rental_date) rental_time
from customer as c
	inner join rental as r
	on c.customer_id = r.customer_id	/*두 테이블 연결 메커니즘*/
where date(r.rental_date) = '2005-06-14'
order by r.rental_date desc;