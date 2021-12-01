select a1.address, a2.address, a1.city_id, a2.city_id
from address as a1
	inner join address as a2
    on a1.city_id = a2.city_id
where a1.address_id <> a2.address_id;