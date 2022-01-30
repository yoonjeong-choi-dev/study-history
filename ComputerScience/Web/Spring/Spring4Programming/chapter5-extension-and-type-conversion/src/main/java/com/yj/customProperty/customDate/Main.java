package com.yj.customProperty.customDate;

import org.springframework.context.support.GenericXmlApplicationContext;

public class Main {
    public static void main(String[] args) {
        GenericXmlApplicationContext ctx = new GenericXmlApplicationContext("classpath:date-config.xml");

        DateWrapper date1 = ctx.getBean("date1", DateWrapper.class);
        DateWrapper date2 = ctx.getBean("date2", DateWrapper.class);

        System.out.println(date1);
        System.out.println(date2);
    }
}
