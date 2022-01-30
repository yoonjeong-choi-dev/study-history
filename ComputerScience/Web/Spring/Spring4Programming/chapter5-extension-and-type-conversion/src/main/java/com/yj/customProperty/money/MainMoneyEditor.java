package com.yj.customProperty.money;

import org.springframework.context.support.GenericXmlApplicationContext;

public class MainMoneyEditor {
    public static void main(String[] args) {
        GenericXmlApplicationContext ctx = new GenericXmlApplicationContext("classpath:money-editor.xml");

        MoneyWrapper mw1 = ctx.getBean("moneyWrap1", MoneyWrapper.class);
        MoneyWrapper mw2 = ctx.getBean("moneyWrap2", MoneyWrapper.class);

        System.out.println(mw1.getMoney());
        System.out.println(mw2.getMoney());
    }
}
