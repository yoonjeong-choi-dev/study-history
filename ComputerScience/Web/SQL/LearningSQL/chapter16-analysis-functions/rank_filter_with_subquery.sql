select first_name, last_name, customer_id, rental_month, num_rental, rank_rank ranking
from
(
	/* 매달 상위 5명의 고객을 찾기 위한 서브쿼리*/
	select c.first_name, c.last_name, c.customer_id, 
		monthname(r.rental_date) rental_month,
		count(*) num_rental,
		/* 월별 랭킹을 위해 partition by로 윈도우 정의*/
		rank() over (
			partition by monthname(rental_date)
			order by count(*) desc) rank_rank
	from rental as r
	inner join customer as c
		on c.customer_id = r.customer_id
	group by r.customer_id, monthname(r.rental_date)
	order by 4, 5 desc
) as cust_rankings
where rank_rank <= 5
order by 4, 5 desc, 6;