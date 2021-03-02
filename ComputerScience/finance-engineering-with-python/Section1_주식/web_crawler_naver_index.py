from urllib.request import urlopen
from bs4 import BeautifulSoup
import datetime as dt


def date_format(date_str):
    date_str = str(date_str).replace("-", ".")
    token = date_str.split(".")
    year = int(token[0])
    month = int(token[1])
    day = int(token[2])

    return dt.date(year, month, day)

KPI200 = "KPI200"
KOSPI = "KOSPI"



def korean_index_naver_one_page(index_code, page_number, start_date, end_date,  historical_prices):
    naver_index_url = "https://finance.naver.com/sise/sise_index_day.nhn?code=" + index_code + "&page=" + str(
        page_number)

    source = urlopen(naver_index_url)
    source = BeautifulSoup(source, "html.parser")

    dates = source.find_all("td", class_="date")
    prices = source.find_all("td", class_="number_1")

    # 날짜 및 주가 추출
    for i in range(len(dates)):
        if dates[i].text.split(".")[0].isdigit():
            # 날짜 처리
            date_str = dates[i].text
            date = date_format(date_str)
            #print(date)

            # 종가 처리 : number_1 클래스 중 0,4,8.. 번째 데이터
            close_price = prices[i*4].text
            close_price = close_price.replace(",", "")
            close_price = float(close_price)

            # 데이터 저장
            if end_date >= date >= start_date:
                historical_prices[date] = close_price
            # start_date 이전 기록은 필요없음 => 종료
            elif date < start_date:
                return False

    return True


def korean_index_naver(index_code, start_date="", end_date=""):
    if start_date:
        start_date = date_format(start_date)
    else:
        start_date = dt.date.today()

    if end_date:
        end_date = date_format(end_date)
    else:
        end_date = dt.date.today()

    naver_index_url = "https://finance.naver.com/sise/sise_index_day.nhn?code=" + index_code + "&page=" + str(
        1)

    # 마지막 페이지 계산
    source = urlopen(naver_index_url)
    source = BeautifulSoup(source, "html.parser")
    paging = source.find("td", class_="pgRR").find("a")["href"]
    last_page_num = int(paging.split("&")[1].split("=")[1])

    historical_prices = dict()

    for i in range(1, last_page_num+1):
        isContinued = korean_index_naver_one_page(index_code, i, start_date, end_date, historical_prices)
        if isContinued is False:
            break

    return historical_prices



if __name__ == "__main__":
    historical_data = korean_index_naver(KPI200, "2018-4-1", "2018-4-4")
    print(historical_data)

    kospi = korean_index_naver(KOSPI)
    print(kospi)













