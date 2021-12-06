/* 방식 1 : 쿼리 전체에 대한 조인 */
select f.film_id, f.title, f.description 
from film as f
inner join film_category as fa
on f.film_id = fa.film_id
where fa.category_id = (select category_id from category where name = 'Action');

/* 방식 2 : 서브 쿼리 내부에 대한 조인 */
select film_id, title, description 
from film 
where film_id in (
	select film_id from film_category as fa
    inner join category as c
    on fa.category_id = c.category_id
    where c.name = 'Action'
);