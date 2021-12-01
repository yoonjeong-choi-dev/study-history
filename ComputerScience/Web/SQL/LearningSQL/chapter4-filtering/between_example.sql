select customer_id, payment_date, amount
from payment
where amount between 10.0 and 11.99
order by amount desc;