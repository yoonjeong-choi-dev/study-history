create view country_total_payments
( country, total_payments ) as 
select ctr.country,
(
	select sum(p.amount) from payment as p
    inner join customer as c
		on c.customer_id = p.customer_id
	inner join address as a
		on c.address_id = a.address_id
	inner join city as ct
		on a.city_id = ct.city_id
	where ct.country_id = ctr.country_id
) total_payments
from country as ctr;