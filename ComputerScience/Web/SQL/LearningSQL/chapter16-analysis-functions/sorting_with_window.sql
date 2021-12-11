select quarter(payment_date) quarter,
	monthname(payment_date) month_name,
    sum(amount) monthly_sales,
    /*분기별 각 달에 대한 판매량 순위 : 순위 생성을 위해 판매량에 대한 내림차순 정렬*/
    rank() over (
		partition by quarter(payment_date)
		order by sum(amount) desc ) sales_rank
from payment
where year(payment_date) = 2005
/* 각 분기 및 달에 대한 그룹핑*/
group by quarter(payment_date), monthname(payment_date)
order by 1, 2;