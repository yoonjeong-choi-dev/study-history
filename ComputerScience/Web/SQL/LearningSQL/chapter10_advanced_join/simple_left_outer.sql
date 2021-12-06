/* inner join : 대여 가능한 영화가 아닌 경우 출력이 불가능*/
select f.film_id, f.title, count(*) num_films
from film as f
inner join inventory as i
on f.film_id = i.film_id
group by f.film_id;

/* outer join : 대여 가능한 영화에 없는 영화들도 0으로 출력 가능*/
select f.film_id, f.title, count(i.inventory_id) num_films
from film as f
left outer join inventory as i
on f.film_id = i.film_id
group by f.film_id;