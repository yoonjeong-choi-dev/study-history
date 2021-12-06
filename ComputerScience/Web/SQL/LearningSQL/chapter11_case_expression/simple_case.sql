/* 프로그래밍 언어에서 지원하는 case 문과 비슷 - 간단한 로직만 처리 */
select ca.custom_rating, count(*) num_films
from (
	select category_id, case name
	when 'Childern' then 'All Ages'
    when 'Family' then 'All Ages'
    when 'Sports' then 'All Ages'
    when 'Animaion' then 'All Ages'
    when 'Horror' then 'Adult'
    when 'Music' then 'Teens'
    when 'Games' then 'Teens'
    else 'Other'
	end custom_rating
	from category) as ca
inner join film_category as fc
on ca.category_id = fc.category_id
inner join film as f
on f.film_id = fc.film_id
group by ca.custom_rating;