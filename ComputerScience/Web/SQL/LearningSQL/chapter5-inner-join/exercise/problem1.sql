select c.first_name, c.last_name, a.address, ct.city
from customer as c
	inner join address as a
    on c.address_id = a.address_id
    inner join city as ct
    on a.city_id = ct.city_id
where a.district = 'California';