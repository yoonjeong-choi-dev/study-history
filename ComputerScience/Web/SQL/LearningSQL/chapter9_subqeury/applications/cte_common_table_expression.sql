with actors_s as (
	select actor_id, first_name, last_name
    from actor
    where last_name like 'S%'
), actors_s_pg as (
	select s.actor_id, s.first_name, s.last_name, f.film_id, f.title
    from actors_s as s
		inner join film_actor as fa
		on s.actor_id = fa.actor_id
		inner join film as f
		on fa.film_id = f.film_id
    where f.rating = 'PG'
), actors_s_pg_revenue as (
	select spg.first_name, spg.last_name, p.amount
    from actors_s_pg as spg
		inner join inventory as i
        on i.film_id = spg.film_id
        inner join rental as r
        on i.inventory_id = r.inventory_id
        inner join payment as p
        on r.rental_id = p.rental_id
) -- cte end : 필수적인 라인
select spg_rev.first_name, spg_rev.last_name, sum(spg_rev.amount) total_revenue
from actors_s_pg_revenue as spg_rev
group by spg_rev.first_name, spg_rev.last_name
order by 3 desc;
