select payment_id, customer_id, amount, date(payment_date)
from payment
where amount in (1.98, 7.98, 9.98);