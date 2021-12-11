select year_no, month_no, total_sales, 
	rank() over (partition by year_no order by total_sales desc)
from Sales_Fact
group by 4;