select f.title,
	case (select count(*) from inventory as i
			where i.film_id = f.film_id)
		when 0 then 'Out of Stock'
        when 1 then 'Scarce'
        when 2 then 'Scarce'
        when 3 then 'Available'
        when 4 then 'Available'
        else 'Common'
	end film_availability
from film f;