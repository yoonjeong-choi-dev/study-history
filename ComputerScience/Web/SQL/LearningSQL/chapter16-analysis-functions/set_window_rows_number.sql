select yearweek(payment_date) payment_week,
	sum(amount) week_total,
    /* 주에 대한 누적 합계 */
    sum(sum(amount)) over (
		/*rows unbounded preceding : n-th 월에는 n개의 행이 존재*/
		order by yearweek(payment_date) rows unbounded preceding
	) rolling_sum,
    /* 1주 전,후를 포함한 평균 : 행 기준 (없는 행에 대한 주는 무시)*/
    avg(sum(amount)) over (
		/*rows between 1 preceding and 1 following : 현재 및 이전/이후 주에 대한 평균*/
		order by yearweek(payment_date) rows between 1 preceding and 1 following
	) rolling_3week_avg
from payment
group by yearweek(payment_date)
order by 1; 