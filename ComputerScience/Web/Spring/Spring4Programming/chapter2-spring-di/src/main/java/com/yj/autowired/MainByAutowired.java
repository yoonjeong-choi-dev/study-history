package com.yj.autowired;

import org.springframework.context.support.GenericXmlApplicationContext;

public class MainByAutowired {
    public static void main(String[] args) {
        GenericXmlApplicationContext ctx = new GenericXmlApplicationContext("classpath:autowired.xml");
        FactoryService myService = ctx.getBean("factoryService", FactoryService.class);

        myService.testFactory();
        myService.testQualifier();
    }
}
