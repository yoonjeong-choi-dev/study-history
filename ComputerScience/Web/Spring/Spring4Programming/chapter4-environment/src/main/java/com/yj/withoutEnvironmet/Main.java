package com.yj.withoutEnvironmet;

import org.springframework.context.annotation.AnnotationConfigApplicationContext;

public class Main {
    public static void main(String[] args) {
        AnnotationConfigApplicationContext ctx = new AnnotationConfigApplicationContext(DBConfig.class);
        DBConnection myConn = ctx.getBean("myConn", DBConnection.class);

        myConn.connect();
    }
}
