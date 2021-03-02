from web_crawler_naver_index import korean_index_naver, KPI200
from json_crawler_naver_index import global_index_naver, SnP500

import pandas as pd
import matplotlib.pyplot as plt
import datetime as dt
import numpy as np
from sklearn.linear_model import LinearRegression

# 데이터 불러오기
start_date = "2008-1-1"
end_date = "2017-12-31"
kospi200 = korean_index_naver(KPI200, start_date, end_date)
sp500 = global_index_naver(SnP500, start_date, end_date)


# 시계열 데이터 처리
kospi200 = pd.Series(kospi200)
sp500 = pd.Series(sp500)
tmp = {'S&P500':sp500, 'KOSPI200':kospi200}
data_frame = pd.DataFrame(tmp)

# 데이터 보간 : 나라별로 휴장일이 달라 비어있는 데이터가 존재
# => 앞이나 뒤의 데이터로 보간한다
data_frame = data_frame.fillna(method="ffill")  # 앞의 데이터로 보간
# 앞의 데이터가 없는 경우에는 뒤에 데이터로 보간
if data_frame.isnull().values.any():
    data_frame = data_frame.fillna(method="bfill")


# 2016년도 이후 데이터 지수화
data_frame_2016 = data_frame.loc[dt.date(2016, 1, 1):]/data_frame.loc[dt.date(2016, 1, 4)]*100

# 회귀 분석 : S&P가 KOSPI에 미치는 영향
import numpy as np
from sklearn.linear_model import LinearRegression

# y : KOSPI, x: S&P
x = data_frame_2016["S&P500"]
y = data_frame_2016["KOSPI200"]

# LinearRegression을 사용하기 위한 벡터 형태 변경 i.e transpose
independent_variable = np.array(x).reshape(-1, 1)
dependent_variable = np.array(y).reshape(-1, 1)

# Linear Regression
reg = LinearRegression()
reg.fit(independent_variable, dependent_variable)

result = {
    "Slope" : reg.coef_[0,0],
    "Intercept": reg.intercept_[0],
    "R^2": reg.score(independent_variable, dependent_variable)
}


# 선형 회귀 시각화
plt.figure(figsize=(5,5))
plt.scatter(independent_variable, dependent_variable, marker=".", color="skyblue")
plt.plot(independent_variable, reg.predict(independent_variable), color="r", linewidth=3)
plt.grid(True, color="0.7", linestyle=":", linewidth=1)
plt.xlabel("S&P500")
plt.ylabel("KOSPI200")