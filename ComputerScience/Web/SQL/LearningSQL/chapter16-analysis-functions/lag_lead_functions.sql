select yearweek(payment_date) payment_week,
	sum(amount) week_total,
    /* 결과 셋의 이전 행 검색 */
    lag(sum(amount), 1) over (
		order by yearweek(payment_date)) prev_week_total,
	/* 결과 셋의 다음 행 검색 */
	lead(sum(amount), 1) over (
		order by yearweek(payment_date)) next_week_total,
	/* 결과 셋의 이전 행을 이용한 변화율 계산*/
	round(
		(sum(amount) - lag(sum(amount), 1) over ( order by yearweek(payment_date) ) )
        / lag(sum(amount), 1)  over ( order by yearweek(payment_date) ) * 100, 1
        ) percentage_diff
from payment
group by yearweek(payment_date)
order by 1;