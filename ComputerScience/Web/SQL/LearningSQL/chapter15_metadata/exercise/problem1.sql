select table_name, column_name, index_name
from information_schema.statistics
where table_schema = 'sakila' 
order by 1, 2;