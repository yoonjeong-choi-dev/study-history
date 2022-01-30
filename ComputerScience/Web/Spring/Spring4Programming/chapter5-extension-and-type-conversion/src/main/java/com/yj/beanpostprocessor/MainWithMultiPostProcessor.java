package com.yj.beanpostprocessor;

import org.springframework.context.support.GenericXmlApplicationContext;

import java.util.Date;

public class MainWithMultiPostProcessor {
    public static void main(String[] args) {
        GenericXmlApplicationContext ctx = new GenericXmlApplicationContext("classpath:beanpostprocessors-config.xml");

        StockReader sr = ctx.getBean("stockReader2", StockReader.class);
        System.out.println("stockReader = " + sr.getClass().getName());

        Date date = new Date();
        sr.getClosePrice(date, "0000");
        sr.getClosePrice(date, "0000");
        sr.getClosePrice(date, "1234");

        ctx.close();
    }
}

