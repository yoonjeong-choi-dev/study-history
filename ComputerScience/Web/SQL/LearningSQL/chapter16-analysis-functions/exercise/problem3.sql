select year_no, month_no, total_sales, 
	lag(total_sales, 1) over (order by month_no) prev_salse
from Sales_Fact
where year_no = 2020
group by 4;