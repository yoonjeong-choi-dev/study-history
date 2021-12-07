create view customer_vw
( customer_id, first_name, last_name, email
) as
select customer_id, first_name, last_name, concat(substr(email,1,2), '*****', substr(email, -4)) email
from customer;