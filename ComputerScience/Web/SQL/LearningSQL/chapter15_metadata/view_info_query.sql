select table_name, is_updatable
from information_schema.views
where table_schema = 'sakila'
order by 1;