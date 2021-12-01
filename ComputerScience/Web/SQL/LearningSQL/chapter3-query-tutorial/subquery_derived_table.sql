select concat(c.last_name, ', ', c.first_name, ': ', c.email) full_name
from
	( select first_name, last_name, email
		from customer
        where first_name = 'JESSIE'
	) c;