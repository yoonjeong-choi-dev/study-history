select fa.actor_id, fa.film_id 
from film_actor as fa
where fa.actor_id in (
	select actor_id from actor where last_name = 'MONROE'
) 
and fa.film_id in (
	select film_id from film where rating = 'PG'
);

/* Same Result */
select fa.actor_id, fa.film_id 
from film_actor as fa
where (fa.actor_id, fa.film_id) in (
	select a.actor_id, f.film_id
    from actor as a
		cross join film as f
    where last_name = 'MONROE'
    and f.rating = 'PG'
);