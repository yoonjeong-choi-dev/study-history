package com.yj.scope;

import org.springframework.context.support.GenericXmlApplicationContext;

public class Main {
    public static void main(String[] args) {
        GenericXmlApplicationContext ctx = new GenericXmlApplicationContext("classpath:scope-config.xml");

        SingletonCounter sc = null;
        System.out.println("[ Singleton Scope ]");
        for(int i=0;i<5;i++){
            sc = ctx.getBean("singleton", SingletonCounter.class);
            sc.info();
        }

        PrototypeCounter pc = null;
        System.out.println("[ Prototype Scope ]");
        for(int i=0;i<5;i++){
            pc = ctx.getBean("prototype", PrototypeCounter.class);
            pc.info();
        }

        ctx.close();
    }
}
