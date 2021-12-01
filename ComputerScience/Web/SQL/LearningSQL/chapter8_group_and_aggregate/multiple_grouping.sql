select fa.actor_id, f.rating, count(*)
from film_actor as fa
	inner join film as f
    on fa.film_id = f.film_id
group by fa.actor_id, f.rating
order by 1,2;