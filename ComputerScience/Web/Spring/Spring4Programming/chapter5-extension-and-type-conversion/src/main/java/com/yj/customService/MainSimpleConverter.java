package com.yj.customService;

import org.springframework.context.support.GenericXmlApplicationContext;

public class MainSimpleConverter {
    public static void main(String[] args) {
        GenericXmlApplicationContext ctx = new GenericXmlApplicationContext("classpath:money-converter.xml");

        MoneyWrapper mw1 = ctx.getBean("moneyWrap1", MoneyWrapper.class);
        MoneyWrapper mw2 = ctx.getBean("moneyWrap2", MoneyWrapper.class);

        System.out.println(mw1.getMoney());
        System.out.println(mw2.getMoney());
    }
}
