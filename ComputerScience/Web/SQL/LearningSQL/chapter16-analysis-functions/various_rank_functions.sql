select c.first_name, c.last_name, c.customer_id, count(*) num_rental,
	/* 동점 처리 1 : 동점인 경우, 각 행이 고유한 순위*/
	row_number() over (order by count(*) desc) row_number_rank,
	/* 동점 처리 2 : 동점은 같은 순위(r), 그 다음 순위가 r+k where r := num(동점 개수)*/
    rank() over (order by count(*) desc) rank_rank,
	/* 동점 처리 3 : 동점은 같은 순위(r), 그 다음 순위는 r+1*/
    dense_rank() over (order by count(*) desc) dense_rank_rank
from rental as r
inner join customer as c
	on c.customer_id = r.customer_id
group by r.customer_id
order by 4 desc;