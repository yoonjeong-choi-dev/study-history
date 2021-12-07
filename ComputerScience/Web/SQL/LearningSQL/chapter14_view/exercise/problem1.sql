create view film_ctgry_actor
( title, category_name, first_name, last_name) 
as 
select f.title, ca.name category_name, a.first_name, a.last_name
from film as f
inner join film_actor as fa
on f.film_id = fa.film_id
inner join actor as a
on fa.actor_id = a.actor_id
inner join film_category as fc
on f.film_id = fc.film_id
inner join category as ca
on fc.category_id = ca.category_id