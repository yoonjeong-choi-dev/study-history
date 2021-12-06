select first_name, last_name,
	case 
		when active = 1 then 'ACTIVE'
        else 'INACTIVE'
	end activity_type
from customer
limit 20;