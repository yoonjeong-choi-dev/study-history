select tbl.table_name,
	(
		select count(*) from information_schema.columns as clm
		where clm.table_schema = tbl.table_schema and clm.table_name = tbl.table_name
	) num_columns,
    (
		select count(*) from information_schema.statistics as sta
		where sta.table_schema = tbl.table_schema and sta.table_name = tbl.table_name
	) num_index,
    (
		select count(*) from information_schema.table_constraints as tc
		where tc.table_schema = tbl.table_schema and tc.table_name = tbl.table_name
			and tc.constraint_type = 'PRIMARY KEY'
	) num_primary_key
from information_schema.tables as tbl
where tbl.table_schema = 'sakila' and tbl.table_type = 'BASE TABLE'
order by 1;