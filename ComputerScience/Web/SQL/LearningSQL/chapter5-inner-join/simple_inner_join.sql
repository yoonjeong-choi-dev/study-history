select c.first_name, c.last_name, a.address 
from customer as c 
	inner join address as a
	on c.address_id = a.address_id;