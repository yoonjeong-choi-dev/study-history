select constraint_name, table_name, constraint_type
from information_schema.table_constraints
where table_schema = 'sakila'
order by 3,1;