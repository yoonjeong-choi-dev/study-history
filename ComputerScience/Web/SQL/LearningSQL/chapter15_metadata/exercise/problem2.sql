with idx_info as (
	select s1.table_name, s1.index_name, s1.column_name, s1.seq_in_index,
	(
		select max(s2.seq_in_index)
        from information_schema.statistics as s2
        where s2.table_schema = s1.table_schema
			and s2.table_name = s1.table_name
            and s2.index_name = s1.index_name
    ) num_columns
	from information_schema.statistics as s1
	where s1.table_schema = 'sakila' and s1.table_name = 'customer'
) --
select concat (
	case
		when seq_in_index = 1 
			then concat('ALTER TABLE ', table_name, ' ADD INDEX ', index_name, ' (', column_name)
		else concat('  , ', column_name)
    end,
    case
		when seq_in_index = num_columns then ');'
        else ''
    end
) index_creation_statment
from idx_info
order by index_name, seq_in_index;