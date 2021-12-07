with idx_info as (
	select s1.index_name, s1.column_name, s1.seq_in_index,
	(
		select max(s2.seq_in_index)
        from information_schema.statistics as s2
        where s2.table_schema = s1.table_schema
			and s2.table_name = s1.table_name
            and s2.index_name = s1.index_name
    ) num_columns
	from information_schema.statistics as s1
	where s1.table_schema = 'sakila' and s1.table_name = 'customer' and s1.index_name <> 'PRIMARY'
) --

select 'create table catogory (' create_table_statement

union all
select cols.txt
from 
	/* Step 1 : 테이블의 열에 대한 정보 추출*/
	(
		select concat('  ', column_name, ' ', column_type,
			case
				when is_nullable = 'NO' then ' not null'
                else ''
			end,
            case
				when extra is not null and extra like 'DEFAULT_GENERATED%'
					then concat(' DEFAULT ', column_default, substr(extra, 18))
				when extra is not null then concat(' ', extra)
                else ''
            end,
            case
				when column_default is not null
					then concat(' default ', column_default)
				else ''
            end,
            ', ') txt
		from information_schema.columns
        where table_schema = 'sakila' and table_name = 'customer'
        order by ordinal_position
    ) cols
    
union all
select concat('  constraint primary key (')
from information_schema.table_constraints
where table_schema = 'sakila' and table_name = 'customer'
    and constraint_type = 'PRIMARY KEY'

union all
select cols.txt
from 
    (select concat(
			case
				when ordinal_position > 1 then '   ,'
                else '   '
			end, 
            column_name) txt
		from information_schema.key_column_usage
        where table_schema = 'sakila' and table_name = 'customer'
			and constraint_name = 'PRIMARY'
        order by ordinal_position
    ) cols

union all
select '  )'

union all
select cols.txt
from
	(select concat (
			case
				when seq_in_index = 1 then concat('  key ', index_name, ' (', column_name)
				else ''
			end,
			case
				when seq_in_index = num_columns then ')'
				else ''
			end
		) txt
		from idx_info
		order by index_name, seq_in_index
    ) cols

union all
select ')';