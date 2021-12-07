select column_name, data_type, character_maximum_length char_max_len,
	numeric_precision num_precision, numeric_scale num_scale
from information_schema.columns
where table_schema = 'sakila' and table_name = 'film'
order by ordinal_position;