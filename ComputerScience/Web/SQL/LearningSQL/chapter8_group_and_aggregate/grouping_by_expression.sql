select extract(year from rental_date) as year, count(*) num_rentals
from rental
group by extract(year from rental_date);