select rental_id, customer_id, return_date
from rental
where
	return_date is null 
    or
    return_date not between '2005-05-01' and '2005-09-01'
order by return_date desc;