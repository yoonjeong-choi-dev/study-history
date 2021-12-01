select customer_id, count(*) num_rental
from rental
group by customer_id
order by count(*) desc;