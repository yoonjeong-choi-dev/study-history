select 
	customer_id,
	max(amount) max_amount, 
	min(amount) min_amount, 
	avg(amount) avg_amount,
    sum(amount) sum_amount,
    count(*) num_payments
from payment
group by customer_id
order by sum_amount desc;