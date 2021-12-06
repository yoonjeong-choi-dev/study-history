select city_id, city
from city
where country_id <> (select country_id from country where country = 'India');