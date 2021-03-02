from scipy import stats
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm


# 잔존만기 계산
def time_to_maturity(current_date, end_date, num_business_day=252):
    current_date = pd.to_datetime(current_date).date()
    end_date = pd.to_datetime(end_date).date()
    return np.busday_count(current_date, end_date)/num_business_day


def call_price(current_price, strike_price, remaining_maturity, interest_rate,  volatility):
    """
    :param current_price: 기초자산 가격
    :param strike_price: 행사 가격
    :param remaining_maturity: 잔존만기(연율 환산)
    :param interest_rate: 이자율(연속 복리)
    :param volatility: 기초자산 변동성
    :return: 콜옵션 이론가
    """
    d1 = (np.log(current_price/strike_price) + (interest_rate+volatility**2*0.5)*remaining_maturity) \
         / (volatility*np.sqrt(remaining_maturity))
    d2 = d1 - volatility*np.sqrt(remaining_maturity)

    call = current_price*stats.norm.cdf(d1, 0.0,1.0) \
           - strike_price *np.exp(-interest_rate*remaining_maturity)*stats.norm.cdf(d2,0.0,1.0)

    return call


def call_price_analysis1():
    ttm = time_to_maturity("2018-9-1", "2018-12-14")
    r = 0.025
    sigma = 0.15

    call_space = dict()
    current_prices = np.arange(200, 400, 5)
    strike_prices = np.arange(250, 350, 10)

    for strike_price in strike_prices:
        single_space = dict()
        for cur_price in current_prices:
            single_space[cur_price] = call_price(cur_price, strike_price, ttm, r, sigma)
        call_space[strike_price] = pd.Series(single_space)

    df_call_space = pd.DataFrame(call_space)

    plt.rcParams["font.family"] = "Malgun Gothic"
    plt.rcParams["font.size"] = 12
    plt.rcParams["axes.unicode_minus"] = False

    fig = plt.figure()
    ax = fig.add_subplot(1,1,1)
    ax.plot(df_call_space[290], label="K=290")
    ax.plot(df_call_space[300], label="K=300")
    ax.plot(df_call_space[310], label="K=310")
    ax.set_xlabel("기초자산(Underlying)")
    ax.set_ylabel("콜옵션가격(Call Price")
    ax.set_title("행사가별 옵션가격")
    ax.legend(loc="best")
    plt.show()

def call_price_analysis2():
    ttm = time_to_maturity("2018-9-1", "2018-12-14")
    r = 0.025
    sigma = 0.15

    current_prices = np.arange(200, 400, 10)
    strike_prices = np.arange(250, 350, 10)

    # meshgrid를 이용하여 2중 반복문을 사용할 필요없이 콜옵션 가격 계산 가능
    current_prices, strike_prices = np.meshgrid(current_prices, strike_prices)
    call_prices = call_price(current_prices, strike_prices, ttm, r, sigma)

    plt.rcParams["font.family"] = "Malgun Gothic"
    plt.rcParams["font.size"] = 12
    plt.rcParams["axes.unicode_minus"] = False

    fig = plt.figure()
    ax = fig.add_subplot(111, projection="3d")

    surf = ax.plot_surface(current_prices, strike_prices, call_prices,
                            cmap=cm.summer, linewidth=1, antialiased=True, alpha=0.8)

    ax.set_xlabel("기초자산(Underlying)")
    ax.set_ylabel("행사가격(Strike)")
    ax.set_zlabel("콜옵션가격(Call Price)")
    ax.set_title("콜 옵션 가격 곡면")

    fig.colorbar(surf, shrink=0.5, aspect=5)
    plt.show()



def put_price(current_price, strike_price, remaining_maturity, interest_rate,  volatility):
    """
    :param current_price: 기초자산 가격
    :param strike_price: 행사 가격
    :param remaining_maturity: 잔존만기(연율 환산)
    :param interest_rate: 이자율(연속 복리)
    :param volatility: 기초자산 변동성
    :return: 풋옵션 이론가
    """
    d1 = (np.log(current_price/strike_price) + (interest_rate+volatility**2*0.5)*remaining_maturity) \
         / (volatility*np.sqrt(remaining_maturity))
    d2 = d1 - volatility*np.sqrt(remaining_maturity)

    put = - current_price*stats.norm.cdf(-d1, 0.0,1.0) \
           + strike_price *np.exp(-interest_rate*remaining_maturity)*stats.norm.cdf(-d2,0.0,1.0)

    return put


def put_price_analysis():
    ttm = time_to_maturity("2018-9-1", "2018-12-14")
    r = 0.025
    sigma = 0.15

    current_prices = np.arange(200, 400, 10)
    strike_prices = np.arange(250, 350, 10)

    current_prices, strike_prices = np.meshgrid(current_prices, strike_prices)
    put_prices = put_price(current_prices, strike_prices, ttm, r, sigma)

    plt.rcParams["font.family"] = "Malgun Gothic"
    plt.rcParams["font.size"] = 12
    plt.rcParams["axes.unicode_minus"] = False

    fig = plt.figure()
    ax = fig.add_subplot(111, projection="3d")

    surf = ax.plot_surface(current_prices, strike_prices, put_prices,
                            cmap=cm.summer, linewidth=1, antialiased=True, alpha=0.8)

    ax.set_xlabel("기초자산(Underlying)")
    ax.set_ylabel("행사가격(Strike)")
    ax.set_zlabel("풋옵션가격(Put Price)")
    ax.set_title("풋 옵션 가격 곡면")

    fig.colorbar(surf, shrink=0.5, aspect=5)
    plt.show()




"""
옵션 그릭스
"""
def call_delta(current_price, strike_price, remaining_maturity, interest_rate,  volatility):
    d1 = (np.log(current_price / strike_price) + (interest_rate + volatility ** 2 * 0.5) * remaining_maturity) \
         / (volatility * np.sqrt(remaining_maturity))

    delta = stats.norm.cdf(d1, 0.0, 1.0)
    return delta


def diff_normal_dist(x):
    return np.exp(-1*x**2*0.5) / np.sqrt(2*np.pi)

def call_gamma(current_price, strike_price, remaining_maturity, interest_rate,  volatility):
    d1 = (np.log(current_price / strike_price) + (interest_rate + volatility ** 2 * 0.5) * remaining_maturity) \
         / (volatility * np.sqrt(remaining_maturity))
    gamma = diff_normal_dist(d1) /(current_price * volatility * np.sqrt(remaining_maturity))
    return gamma

def call_theta(current_price, strike_price, remaining_maturity, interest_rate,  volatility):
    d1 = (np.log(current_price / strike_price) + (interest_rate + volatility ** 2 * 0.5) * remaining_maturity) \
         / (volatility * np.sqrt(remaining_maturity))
    d2 = d1 - volatility * np.sqrt(remaining_maturity)

    theta = -1 * ((current_price * diff_normal_dist(d1) * volatility) / (2 * np.sqrt(remaining_maturity))) \
            - interest_rate * strike_price * np.exp(-interest_rate*remaining_maturity)*stats.norm.cdf(d2, 0.0, 1.0)
    return theta


def call_put_vega(current_price, strike_price, remaining_maturity, interest_rate,  volatility):
    d1 = (np.log(current_price / strike_price) + (interest_rate + volatility ** 2 * 0.5) * remaining_maturity) \
         / (volatility * np.sqrt(remaining_maturity))
    vega = current_price * np.sqrt(remaining_maturity) * diff_normal_dist(d1)
    return vega

def plot_option_greeks():
    ttm = time_to_maturity("2018-9-1", "2018-12-14")
    r = 0.025
    sigma = 0.15

    current_prices = np.arange(200, 400, 10)
    strike_prices = np.arange(300, 350, 5)

    # meshgrid를 이용하여 2중 반복문을 사용할 필요없이 콜옵션 가격 계산 가능
    current_prices, strike_prices = np.meshgrid(current_prices, strike_prices)
    plt.rcParams["font.family"] = "Malgun Gothic"
    plt.rcParams["font.size"] = 12
    plt.rcParams["axes.unicode_minus"] = False

    fig = plt.figure()

    # Delta
    deltas = call_delta(current_prices, strike_prices, ttm, r, sigma)
    ax = fig.add_subplot(221, projection="3d")

    surf = ax.plot_surface(current_prices, strike_prices, deltas,
                           cmap=cm.coolwarm, linewidth=1, antialiased=True, alpha=0.8)

    ax.set_xlabel("기초자산(Underlying)")
    ax.set_ylabel("행사가격(Strike)")
    ax.set_zlabel("델타(Delta)")
    ax.set_title("델타 곡면")

    # Delta
    gamma = call_gamma(current_prices, strike_prices, ttm, r, sigma)
    ax = fig.add_subplot(222, projection="3d")

    surf = ax.plot_surface(current_prices, strike_prices, gamma,
                           cmap=cm.summer, linewidth=1, antialiased=True, alpha=0.8)

    ax.set_xlabel("기초자산(Underlying)")
    ax.set_ylabel("행사가격(Strike)")
    ax.set_zlabel("감마(Gamma)")
    ax.set_title("감마 곡면")

    # Theta
    remaining_maturities = np.arange(1.0, 0.0, -0.01)
    current_prices = np.arange(350, 355)
    remaining_maturities, current_prices = np.meshgrid(remaining_maturities, current_prices)
    thetas = call_theta(current_prices, 350, remaining_maturities, 0.02, 0.30)

    ax = fig.add_subplot(223, projection="3d")

    surf = ax.plot_surface(remaining_maturities,current_prices, thetas,
                           cmap=cm.summer, linewidth=1, antialiased=True, alpha=0.8)

    ax.set_xlabel("잔존만기(Time to Maturity)")
    ax.set_ylabel("기초자산(Underlying)")
    ax.set_zlabel("세타(Theta)")
    ax.set_title("세타 곡면")
    ax.invert_xaxis()


    # Vega
    volatilities = np.arange(0.05, 0.95, 0.01)
    current_prices = np.arange(350, 352)
    volatilities, current_prices = np.meshgrid(volatilities, current_prices)
    vegas = call_put_vega(current_prices, 350, 0.38, 0.02, volatilities)

    ax = fig.add_subplot(224, projection="3d")

    surf = ax.plot_surface(volatilities, current_prices, vegas,
                           cmap=cm.spring, linewidth=1, antialiased=True, alpha=0.8)

    ax.set_xlabel("변동성(Volatility)")
    ax.set_ylabel("기초자산(Underlying)")
    ax.set_zlabel("베가(Vega)")
    ax.set_title("베가 곡면")

    plt.show()





if __name__ == "__main__":
    #call_price_analysis1()
    #call_price_analysis2()
    #put_price_analysis()
    plot_option_greeks()





