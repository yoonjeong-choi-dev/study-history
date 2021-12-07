select index_name, non_unique, seq_in_index, column_name
from information_schema.statistics
where table_schema = 'sakila' and table_name = 'rental'
order by 1, 3;