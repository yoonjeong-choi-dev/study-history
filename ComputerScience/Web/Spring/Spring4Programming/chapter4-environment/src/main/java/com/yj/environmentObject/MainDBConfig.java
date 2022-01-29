package com.yj.environmentObject;

import org.springframework.context.annotation.AnnotationConfigApplicationContext;

public class MainDBConfig {
    public static void main(String[] args) {
        AnnotationConfigApplicationContext ctx = new AnnotationConfigApplicationContext(DBConfig.class);

        BeanWithEnvironmentAware db1 = ctx.getBean("db1", BeanWithEnvironmentAware.class);
        BeanWithAutowired db2 = ctx.getBean("db2", BeanWithAutowired.class);


        db1.connect();
        db2.connect();

        ctx.close();
    }
}
