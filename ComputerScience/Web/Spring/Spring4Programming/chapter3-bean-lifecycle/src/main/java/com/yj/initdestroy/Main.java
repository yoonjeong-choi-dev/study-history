package com.yj.initdestroy;

import org.springframework.context.support.GenericXmlApplicationContext;

public class Main {
    public static void main(String[] args) {
        GenericXmlApplicationContext ctx = new GenericXmlApplicationContext("classpath:config.xml");

        WithInterface ex1 = ctx.getBean("bean1", WithInterface.class);
        ex1.run();

        WithAnnotation ex2 = ctx.getBean("bean2", WithAnnotation.class);
        ex2.run();

        WithCustom ex3 = ctx.getBean("bean3", WithCustom.class);
        ex3.run();

        ctx.close();
    }
}
