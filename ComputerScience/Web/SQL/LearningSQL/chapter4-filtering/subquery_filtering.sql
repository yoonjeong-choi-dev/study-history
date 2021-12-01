/*PET이 들어간 영화와 같은 등급인 영화들*/
select title, rating 
from film
where rating in 
	( select rating from film where title like '%PET%');