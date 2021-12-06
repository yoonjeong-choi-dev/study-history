select city_id, city
from city
where country_id in (select country_id from country where country in ('India', 'Mexico'));