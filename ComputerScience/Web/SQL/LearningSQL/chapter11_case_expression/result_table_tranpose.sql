/* 첫 번째 쿼리 결과를 transpose 하는 방법*/
select monthname(rental_date) rental_month, count(*) num_rentals
from rental
where rental_date between '2005-05-01' and '2005-08-01'
group by monthname(rental_date);

/* 작은 데이터에서 실용적 => SQL 서버 및 오라클은 pivot 기능을 제공*/
select 
	sum(case when monthname(rental_date) = 'May' then 1 else 0 end) May_Rental,
    sum(case when monthname(rental_date) = 'June' then 1 else 0 end) June_Rental,
    sum(case when monthname(rental_date) = 'July' then 1 else 0 end) July_Rental
from rental
where rental_date between '2005-05-01' and '2005-08-01';