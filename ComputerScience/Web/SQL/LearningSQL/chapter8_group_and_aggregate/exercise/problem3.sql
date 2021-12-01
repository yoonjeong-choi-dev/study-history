select customer_id, count(*) num_payments, sum(amount) total_amount
from payment
group by customer_id
having count(*) >= 40
order by count(*);