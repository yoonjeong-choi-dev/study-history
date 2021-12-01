select customer_id, count(*) num_rental
from rental
group by customer_id
having count(*) > 40
order by count(*) desc;