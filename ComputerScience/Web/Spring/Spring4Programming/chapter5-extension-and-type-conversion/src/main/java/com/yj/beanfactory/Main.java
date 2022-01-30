package com.yj.beanfactory;

import org.springframework.context.support.GenericXmlApplicationContext;

public class Main {
    public static void main(String[] args) {
        GenericXmlApplicationContext ctx = new GenericXmlApplicationContext("classpath:beanfactory-config.xml");

        DataCollector dc1 = ctx.getBean("collector1", DataCollector.class);
        DataCollector dc2 = ctx.getBean("collector2", DataCollector.class);

        System.out.println("Set Threshold property : " + dc1.getThreshold());
        System.out.println("Default Threshold property : " + dc2.getThreshold());
    }
}
