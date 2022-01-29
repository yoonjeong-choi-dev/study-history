package com.yj.profile;

import org.springframework.context.support.GenericXmlApplicationContext;

public class Main {
    private static String configPath = "classpath:/profile-config.xml";

    public static void main(String[] args) {
        System.out.println("[ Development ]");
        runDev();

        System.out.println("[ Production ]");
        runProd();
    }

    private static void runDev() {
        GenericXmlApplicationContext ctx = new GenericXmlApplicationContext();
        ctx.getEnvironment().setActiveProfiles("dev");
        ctx.load(configPath);
        ctx.refresh();

        DBConnect conn = ctx.getBean("dbConn", DBConnect.class);
        conn.connect();
        ctx.close();
    }

    private static void runProd() {
        GenericXmlApplicationContext ctx = new GenericXmlApplicationContext();
        ctx.getEnvironment().setActiveProfiles("prod");
        ctx.load(configPath);
        ctx.refresh();

        DBConnect conn = ctx.getBean("dbConn", DBConnect.class);
        conn.connect();
        ctx.close();
    }
}
