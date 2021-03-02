import pandas as pd
from urllib.request import urlopen
import json

NIKKEI225 = "NII@NI225"
SnP500 = "SPI@SPX"


GLOBAL_INDICES = {
    "SPI@SPX" : "S&P 500",
    "NAS@NDX" : "Nasdaq 100",
    "NII@NI225" : "Nikkei 225"
}

def date_format(d=""):
    if d!="":
        date = pd.to_datetime(d).date()
    else:
        # 오늘 날짜로 지정
        date = pd.Timestamp.today().date()

    return date


LAST_DATE = date_format("2003-01-02")

def global_index_naver_one_page(symbol, page_num, start_date, end_date, historical_data):
    url = "https://finance.naver.com/world/worldDayListJson.nhn?symbol=" + symbol + "&fdtc=0&page=" + str(page_num)
    raw_data = urlopen(url)
    json_data = json.load(raw_data)


    for data in json_data:
        date = pd.to_datetime(data["xymd"]).date()

        if start_date <= date<=end_date:
            price = float(data["clos"])
            historical_data[date]=price
        # start_date 이전 기록은 필요없음 => 종료
        elif date < start_date:
            return  False

    # 최초일자 보다 이전 데이터는 존재 x
    if pd.to_datetime(json_data[-1]["xymd"]).date() <= LAST_DATE:
        return False
    else:
        return True



def global_index_naver(symbol, start_date="", end_date=""):
    end_date = date_format(end_date)
    if start_date == "":
        start_date = end_date - pd.DateOffset(months=1)
    start_date = date_format(start_date)

    page = 1

    historical_data = dict()
    isContinued = True
    while isContinued:
        isContinued = global_index_naver_one_page(symbol, page, start_date, end_date, historical_data)
        page += 1

    return historical_data


def global_index_data(start_date="2019-01-01", end_date="2019-03-31"):
    global_data = dict()
    for key, value in GLOBAL_INDICES.items():
        s = global_index_naver(key, start_date, end_date)
        global_data[value] = s


    prices_df = pd.DataFrame(global_data)
    return prices_df


if __name__ == "__main__":
    #test = global_index_data()
    #pd.set_option('display.max_row', 500)
    test = global_index_naver(SnP500, "2019-01-01", "2019-01-10")
    print(test)




























