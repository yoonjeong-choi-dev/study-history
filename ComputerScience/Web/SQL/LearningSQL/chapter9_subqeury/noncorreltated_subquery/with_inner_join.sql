select customer_id, count(*)
from rental
group by customer_id
having count(*) > all
(
	select count(*) 
    from rental as r
		inner join customer as c
		on r.customer_id = c.customer_id
		inner join address as addr
		on c.address_id = addr.address_id
		inner join city as ct
		on addr.city_id = ct.city_id
		inner join country as co
		on ct.country_id = co.country_id
    where co.country in ('United States', 'Mexico', 'Canada')
    group by r.customer_id
);