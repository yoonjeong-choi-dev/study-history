package com.yj.beanpostprocessor;

import java.util.Date;

public interface StockReader {
    public int getClosePrice(Date date, String code);
}
