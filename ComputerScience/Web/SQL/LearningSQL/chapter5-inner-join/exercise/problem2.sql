select f.title, a.first_name, a.last_name
from film as f
	inner join film_actor as fa
    on f.film_id = fa.film_id
    inner join actor as a
    on fa.actor_id = a.actor_id
where a.first_name = 'JOHN' or a.last_name = 'JOHN';