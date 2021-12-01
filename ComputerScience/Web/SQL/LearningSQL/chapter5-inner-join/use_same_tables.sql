select f.title
from film as f
	inner join film_actor as fa1
		on f.film_id = fa1.film_id
	inner join actor as a1
		on fa1.actor_id = a1.actor_id
	inner join film_actor as fa2
		on f.film_id = fa2.film_id
	inner join actor as a2
		on fa2.actor_id = a2.actor_id
where (a1.first_name ='CATE' and a1.last_name = 'MCQUEEN') 
	and (a2.first_name = 'CUBA' and a2.last_name = 'BIRCH');