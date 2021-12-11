select quarter(payment_date) quarter,
	monthname(payment_date) month_name,
    sum(amount) monthly_sales,
    /*over + partition : 윈도우를 정의하고 해당 윈도우로 분석을 위한 임시 그룹핑 기능*/
    max(sum(amount)) over () max_overall_sales,
    max(sum(amount)) over (partition by quarter(payment_date)) max_quarter_sales
from payment
where year(payment_date) = 2005
/* 각 분기 및 달에 대한 그룹핑*/
group by quarter(payment_date), monthname(payment_date);