select film_id, title, description 
from film as f
where exists (
	select 1 from film_category as fa
    inner join category as c
    on fa.category_id = c.category_id
    where c.name = 'Action' and f.film_id = fa.film_id
);