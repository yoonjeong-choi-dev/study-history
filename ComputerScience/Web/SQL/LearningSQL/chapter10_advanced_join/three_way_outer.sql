select f.film_id, f.title, i.inventory_id, r.rental_date
from film as f
left outer join inventory as i
on f.film_id = i.film_id
left outer join rental as r
on i.inventory_id = r.inventory_id
where f.film_id between 13 and 15;