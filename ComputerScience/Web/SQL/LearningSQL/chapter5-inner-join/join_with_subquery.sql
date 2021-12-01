select c.first_name, c.last_name, addr.address, addr.city
from customer as c
	inner join (
		select a.address_id, a.address, ct.city
        from address as a 
			inner join city as ct
            on a.city_id = ct.city_id
		where a.district = 'California'
    ) as addr
    on c.address_id = addr.address_id;