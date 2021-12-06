/*각 필드에 대해서 서브쿼리 수행*/
select (
	select c.first_name from customer as c
    where c.customer_id = p.customer_id
) first_name, (
	select c.last_name from customer as c
    where c.customer_id = p.customer_id
) last_name, (
	select ct.city from customer as c
		inner join address as a
		on c.address_id = a.address_id
		inner join city as ct
		on ct.city_id = a.city_id
	where c.customer_id = p.customer_id
) city, sum(p.amount) total_payments, count(*) total_rentals
from payment as p
group by p.customer_id;