select customer_id, count(*) num_payments, sum(amount) total_amount
from payment
group by customer_id
order by count(*);