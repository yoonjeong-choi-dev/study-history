select c.first_name, c.last_name
from customer as c
where 20 = (
	select count(*) from rental r
    where r.customer_id = c.customer_id
);