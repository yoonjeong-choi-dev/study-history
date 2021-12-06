select customer_id, first_name, last_name
from customer
where customer_id = (select max(customer_id) from customer);