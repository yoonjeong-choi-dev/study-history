/* group by 결과로 출련된 항목들에 대한 집계 */
select fa.actor_id, f.rating, count(*) num_film
from film_actor as fa
	inner join film as f
    on fa.film_id = f.film_id
group by fa.actor_id, f.rating with rollup
order by 1,2;