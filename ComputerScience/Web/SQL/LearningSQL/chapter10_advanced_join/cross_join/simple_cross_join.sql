select c.name category_name, l.name language_name
from category as c
cross join language as l;