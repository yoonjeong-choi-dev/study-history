select c.first_name, c.last_name, sum(p.amount)
from customer as c
left outer join payment as p
on c.customer_id = p.customer_id
group by c.customer_id