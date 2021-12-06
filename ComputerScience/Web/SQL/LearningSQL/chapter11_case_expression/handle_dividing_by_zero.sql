select c.first_name, c.last_name, sum(p.amount) total_payment, count(p.amount) num_payment, 
	/* 평균 계산 : 대여 기록이 없는 고객에 대해서는 분모가 0*/
	sum(p.amount) / case 
						when count(p.amount) = 0 then 1 else count(p.amount)
						end average_payment
from customer as c
left outer join payment as p
on c.customer_id = p.customer_id
group by c.customer_id;