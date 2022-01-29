package com.yj.locale;

import java.io.IOException;
import java.util.Locale;
import org.springframework.context.support.GenericXmlApplicationContext;

public class Main {
    public static void main(String[] args) {
        GenericXmlApplicationContext ctx = new GenericXmlApplicationContext("classpath:message-conf.xml");

        System.out.println("[ 현재 언어 설정 : Locale.getDefault() ]");
        System.out.println(ctx.getMessage("hello", null, Locale.getDefault()));
        System.out.println(ctx.getMessage("welcome", new String[]{"최윤정"}, Locale.getDefault()));
        System.out.println("Current Language : " + ctx.getMessage("lang", null, Locale.getDefault()));

        System.out.println("\n\n[ 현재 언어 설정 : Locale.ENGLISH ]");
        System.out.println(ctx.getMessage("hello", null, Locale.ENGLISH));
        System.out.println(ctx.getMessage("welcome", new String[]{"Yoonjeong"}, Locale.ENGLISH));
        System.out.println("Current Language : " + ctx.getMessage("lang", null, Locale.ENGLISH));
    }
}
