select subpay_group.name, count(*) num_customers
from (
	/* 쿼리 대상 테이블 정의 : 각 고객에 대한 대여 횟수 및 대여 비용 쿼리 */
	select customer_id, count(*) num_rentals, sum(amount) total_payments
	from payment
    group by customer_id
	) as subpay
inner join 
	(
	/* 그룹핑에 사용할 새로운 그룹 정의*/
	select 'Small Customers' name, 0 low_limit, 74.99 high_limit
	union all
	select 'Average Customers' name, 75 low_limit, 149.99 high_limit
	union all
	select 'Heavy Customers' name, 150 low_limit, 999999.9 high_limit
	) as subpay_group
    on subpay.total_payments between subpay_group.low_limit and subpay_group.high_limit
/* 그룹핑할 대상 정의*/
group by subpay_group.name;