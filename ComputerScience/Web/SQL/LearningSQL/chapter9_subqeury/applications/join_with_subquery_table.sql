select c.first_name, c.last_name, subpay.num_rentals, subpay.total_payments
from customer as c
inner join 
	(
		select customer_id, count(*) num_rentals, sum(amount) total_payments
        from payment
        group by customer_id
	) as subpay
	on c.customer_id = subpay.customer_id;