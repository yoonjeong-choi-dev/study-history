select c.first_name, c.last_name, count(*)
from customer c
	inner join rental r
    on c.customer_id = r.customer_id
    group by c.first_name, c.last_name
    having count(*) >= 40;