select p.payment_id, p.customer_id, p.amount, date(p.payment_date) 
from (select * from payment where payment_id between 101 and 120) as p
where customer_id <> 5 and (amount > 8 or date(payment_date) = '2005-08-23');