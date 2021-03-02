import pandas as pd
import numpy as np


def load_wti_data():
    kospi_data_file = "WTI Feature Data.xlsx"

    # 현물 가격
    spot = pd.read_excel(kospi_data_file, "Spot", index_col="Date", usecols="A:B", engine="openpyxl")

    # 최근월물 가격 : 만기를 앞두고 있는 선물
    front = pd.read_excel(kospi_data_file, "Front", index_col="Date", usecols="A:B", engine="openpyxl")

    # 차근월물 가격 : 다음 주기에 만기가 도래할 선물
    second = pd.read_excel(kospi_data_file, "Second", index_col="Date", usecols="A:B", engine="openpyxl")

    data_frame = pd.concat([spot, front, second], axis=1)

    # NaN 처리
    data_frame = data_frame.fillna(method="ffill")
    data_frame = data_frame.fillna(method="bfill")

    # 만기일 정보 : 만기일에 롤오버를 시행하기 위해 필요
    expiry = pd.read_excel(kospi_data_file, "Expiry", usecols="A:D", engine="openpyxl")
    expiry = pd.Series(pd.to_datetime(expiry["Last Trade"]))

    # 데이터프레임에 최종 거래일 표시
    data_frame["Expiry"] = np.nan
    for date in data_frame.index:
        # expiry에 해당 날짜가 있으면 표시
        if date in pd.to_datetime(expiry.values):
            data_frame.loc[date].Expiry = 1


    return data_frame



def calculate_profit():
    data_frame = load_wti_data()
    
    final_date = "2017-12-28"
    init_date = "2010-01-04"

    # 현물 투자 시, 손익 계산 : 현재가격-초기가격
    price_now = float(data_frame[final_date]["Spot"])
    price_before = float(data_frame[init_date]["Spot"])
    profit = (price_now-price_before)*1000

    print("현물 투자 손익(현재가-초기가) : {:,.2f}".format(profit))

    # 선물 투자 시, 손익 계산
    # 만기마다 롤오버
    # : 최근월물을 팔고, 차근월물을 매입

    # 롤오버 비용 계산
    roll_over_cost_acc=0
    for date in data_frame.index:
        # 최종 거래일이면 롤오버
        if data_frame.loc[date].Expiry == 1:
            # 롤오버 비용 : 차근 월물 가격(매입) - 최근 월물 가격(매도)
            roll_over_cost = data_frame.loc[date].Second - data_frame.loc[date].Front
            roll_over_cost_acc += roll_over_cost

    print("누적 롤 오버 비용 : {:,.2f}".format(roll_over_cost_acc))

    # 선물 손익 계산
    price_now = float(data_frame[final_date]["Front"])
    price_before = float(data_frame[init_date]["Front"])
    profit = (price_now - price_before - roll_over_cost_acc)*1000

    print("선물 투자 손익(현재가-초기가-롤오버비용) : {:,.2f}".format(profit))















if __name__ == "__main__":
    calculate_profit()