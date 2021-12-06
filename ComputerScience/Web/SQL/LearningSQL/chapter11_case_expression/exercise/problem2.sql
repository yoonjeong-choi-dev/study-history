select 
	sum(case when rating = 'PG' then 1 else 0 end) PG,
    sum(case when rating = 'G' then 1 else 0 end) G,
    sum(case when rating = 'NC-17' then 1 else 0 end) 'NC-17',
    sum(case when rating = 'PG-13' then 1 else 0 end) 'PG-13',
    sum(case when rating = 'R' then 1 else 0 end) R
from film;