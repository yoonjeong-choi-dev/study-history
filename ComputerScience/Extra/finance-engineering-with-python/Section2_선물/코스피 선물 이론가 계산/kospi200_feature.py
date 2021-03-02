import pandas as pd
import numpy as np


def load_excel_file():
    kospi_data_file = "KOSPI200 Feature Data.xlsx"

    # 엑셀 파일을 읽어 데이터프레임으로 만들기
    data_frame = pd.read_excel(kospi_data_file, "Sheet1", index_col="일자", usecols="A:C", engine="openpyxl")

    # 날짜 관련 문자열을 날짜 형식으로 변환
    data_frame.index = pd.to_datetime(data_frame.index)

    return data_frame


# 연속복리이자율 기반
def future_price_continuous_compound(current_value, interest_rate, dividend_rate, final_date, cur_date):
    """
    :param current_value: 현물 가격
    :param interest_rate: 이자율
    :param dividend_rate: 배당율
    :param final_date: 최종 거래일
    :param cur_date: 현재 날짜
    :return: 선물 가격
    """
    DATES_PER_YEAR = 252
    remaining_maturity = np.busday_count(cur_date.date(), final_date.date()) / DATES_PER_YEAR
    future_price = current_value*np.exp((interest_rate - dividend_rate)*remaining_maturity)
    return future_price


# 단리이자율 기반
def future_price_simple_compound(current_value, interest_rate, dividend_rate, final_date, cur_date):
    """
    :param current_value: 현물 가격
    :param interest_rate: 이자율
    :param dividend_rate: 배당율
    :param final_date: 최종 거래일
    :param cur_date: 현재 날짜
    :return: 선물 가격
    """
    DATES_PER_YEAR = 365
    remaining_maturity = (final_date-cur_date).days / DATES_PER_YEAR
    future_price = current_value*(1+(interest_rate - dividend_rate)*remaining_maturity)
    return future_price


# 코스피 데이터 이론가 산출
def calculate_kospi_futures():
    data_frame = load_excel_file()
    final_date = pd.to_datetime("2017-12-14")
    interest_rate = 0.0225
    dividend_rate = 0.015


    for date in data_frame.index:
        current_value = data_frame.loc[date, "지수"]

        # 이론가 1 : 연속복리이자율
        future_price = future_price_continuous_compound(current_value, interest_rate, dividend_rate, final_date, date)
        price = "{:,.2f}".format(future_price)
        data_frame.loc[date, "이론가1"] = price

        # 이론가 2 : 단리 이자율
        future_price = future_price_simple_compound(current_value, interest_rate, dividend_rate, final_date, date)
        price = "{:,.2f}".format(future_price)
        data_frame.loc[date, "이론가2"] = price

    print(data_frame.head())
















if __name__ == "__main__":
    calculate_kospi_futures()





