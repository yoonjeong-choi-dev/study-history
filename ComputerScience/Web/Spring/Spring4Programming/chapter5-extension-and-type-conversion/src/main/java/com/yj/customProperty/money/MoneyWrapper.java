package com.yj.customProperty.money;

// MoneyEditor 테스트를 위한 래퍼 클래스
public class MoneyWrapper {
    private Money money;

    public Money getMoney() {
        return money;
    }

    public void setMoney(Money money) {
        this.money = money;
    }
}
