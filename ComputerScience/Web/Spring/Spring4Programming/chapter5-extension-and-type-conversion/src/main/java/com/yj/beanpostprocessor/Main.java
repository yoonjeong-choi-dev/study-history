package com.yj.beanpostprocessor;

import com.yj.beanfactory.DataCollector;
import org.springframework.context.support.GenericXmlApplicationContext;

import java.util.Date;

public class Main {
    public static void main(String[] args) {
        GenericXmlApplicationContext ctx = new GenericXmlApplicationContext("classpath:beanpostprocessor-config.xml");

        StockReader sr = ctx.getBean("stockReader", StockReader.class);
        Date date = new Date();
        printClosePrice(sr, date, "0000");
        printClosePrice(sr, date, "0000");
        printClosePrice(sr, date, "1234");

        ctx.close();
    }

    private static void printClosePrice(StockReader sr, Date date, String code) {
        long before = System.currentTimeMillis();
        int stockPrice = sr.getClosePrice(date, code);
        long after = System.currentTimeMillis();

        System.out.println("Price : " + stockPrice + ", execution time : " + (after - before));
    }
}
