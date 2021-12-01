select 
	max(amount) max_amount, 
	min(amount) min_amount, 
	avg(amount) avg_amount,
    sum(amount) sum_amount,
    count(*) num_payments
from payment;