/* with sql_mode=only_full_group_by 에러 처리를 위한 임시 mode 설정*/
SET SESSION sql_mode = 'STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

select monthname(payment_date) payment_month,
	amount,
    /*월 별 판매량 */
    sum(amount) over (
		partition by monthname(payment_date)) month_total,
	/*연간 판매량에서 월 별 비율*/
	round(sum(amount) / sum(sum(amount)) over () * 100, 2) monthly_ratio,
    /* 월 별 판매량에 대한 레이블링*/
    case sum(amount)
		when max(sum(amount)) over () then 'Highest'
        when min(sum(amount)) over () then 'Lowest'
        else 'Middel'
	end descriptor
from payment
group by monthname(payment_date)
order by 4 desc;