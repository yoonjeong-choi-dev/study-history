/* 배우가 출연한 영화 개수를 이용하여 정렬*/
select a.actor_id, a.first_name, a.last_name
from actor as a
order by (
	select count(*) from film_actor as fa
    where fa.actor_id = a.actor_id
) desc;

/* 다음과 같은 inner join + group 으로 같은 결과 나옴*/
select a.actor_id, a.first_name, a.last_name, count(*)
from actor as a
    inner join film_actor as fa
        on fa.actor_id = a.actor_id
group by a.actor_id
order by 4 desc;