select c.first_name, c.last_name, sum(p.amount)
from payment as p
right outer join customer as c
on c.customer_id = p.customer_id
group by c.customer_id