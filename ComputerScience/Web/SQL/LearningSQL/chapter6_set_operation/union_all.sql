select c.first_name, c.last_name 
from customer as c
where c.first_name like 'J%' and c.last_name like 'D%'
union all
select a.first_name, a.last_name
from actor a
where a.first_name like 'J%' and a.last_name like 'D%';