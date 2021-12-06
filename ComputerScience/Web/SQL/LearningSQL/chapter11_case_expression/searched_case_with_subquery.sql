/*
활성화 고객 비율이 적은 경우, 활성화 고객에 대해서만 테이블 조인
*/
select c.first_name, c.last_name,
	case 
		when active = 1 then 0
        else (
			select count(*) from rental as r
            where c.customer_id = r.customer_id
        )
	end num_rentals
from customer as c
limit 20;