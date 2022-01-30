package com.yj.beanpostprocessor;

import java.util.Date;

public class SomeStockReader implements StockReader{
    @Override
    public int getClosePrice(Date date, String code) {
        System.out.println("Some Stock Reader : " + code);

        // 캐시를 이용하는 확장 기능 테스트를 위한 해당 예제를 위한 코드
        try {
            Thread.sleep(300);
        } catch (InterruptedException e) {

        }

        return 500;
    }
}
