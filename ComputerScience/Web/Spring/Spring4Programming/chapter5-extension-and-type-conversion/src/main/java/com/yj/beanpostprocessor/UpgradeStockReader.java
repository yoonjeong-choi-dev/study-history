package com.yj.beanpostprocessor;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

public class UpgradeStockReader implements StockReader {

    private Map<String, Integer> cache = new HashMap<String, Integer>();
    private StockReader delegate;   // 변경시켜야 하는 클래스

    public UpgradeStockReader(StockReader delegate) {
        this.delegate = delegate;
    }

    @Override
    public int getClosePrice(Date date, String code) {
        String key = createKey(date, code);
        System.out.println("[upgrade]Check the cache with the key : " + key);
        if(cache.containsKey(key)) {
            return cache.get(key);
        }

        // 캐시에 없는 경우, 기존 클래스 객체(대리자)를 이용하여 작업 수행
        int value = delegate.getClosePrice(date, code);
        cache.put(key, value);

        return value;
    }

    private String createKey(Date date, String code) {
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyyMMdd");
        return dateFormat.format(date) + code;
    }
}
