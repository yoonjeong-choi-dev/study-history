select a.first_name, a.last_name, actor_groups.level, a.num_films
from (
	select first_name, last_name, count(*) num_films
    from actor as a
    inner join film_actor as f
    on a.actor_id = f.actor_id
    group by a.actor_id
) as a
inner join ( select 'Hollywood Star' level, 30 min_roles, 999999 max_roles
	union all
	select 'Prilific Actor' level, 20 min_roles, 29 max_roles
	union all
	select 'Newcomer' level, 1 min_roles, 19 max_roles
	) as actor_groups
on a.num_films between actor_groups.min_roles and actor_groups.max_roles;