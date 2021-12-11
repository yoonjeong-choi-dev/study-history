/* 각 영화에 대해서 출연한 배우 모두 출력*/
select f.title, 
	group_concat(a.last_name order by a.last_name separator ', ') actors
from actor as a
inner join film_actor as fa
	on a.actor_id = fa.actor_id
inner join film as f
	on fa.film_id = f.film_id
group by f.title
