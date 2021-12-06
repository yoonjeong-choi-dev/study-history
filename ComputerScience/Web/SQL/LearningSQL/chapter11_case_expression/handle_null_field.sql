select c.first_name, c.last_name,
	case 
		when a.address is null then 'Unknown'
        else a.address
	end address,
    case 
		when ct.city is null then 'Unknown'
		else ct.city
	end city,
    case
		when cn.country is null then 'Unknown'
        else cn.country
	end country
from customer as c
left outer join address as a
	on c.address_id = a.address_id
left outer join city as ct
	on a.city_id = ct.city_id
left outer join country as cn
	on ct.country_id = cn.country_id;