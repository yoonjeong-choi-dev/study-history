select first_name, last_name
from customer
where customer_id <> ALL (
	select customer_id
    from payment
    where amount = 0
);