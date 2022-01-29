package com.yj.environmentObject;

import org.springframework.context.ConfigurableApplicationContext;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.core.env.ConfigurableEnvironment;

import java.util.Map;

public class MainEnvironment {
    public static void main(String[] args) {
        ConfigurableApplicationContext ctx = new AnnotationConfigApplicationContext();
        ConfigurableEnvironment env = ctx.getEnvironment();

        Map<String, Object> systemEnv = env.getSystemEnvironment();
        System.out.println("System Environment");
        for(String key : systemEnv.keySet()) {
            System.out.println(key+ " : " + systemEnv.get(key));
        }

        Map<String, Object> propEnv = env.getSystemProperties();
        System.out.println("\n\nSystem Properties");
        for(String key : propEnv.keySet()) {
            System.out.println(key+ " : " + propEnv.get(key));
        }

        ctx.close();
    }
}
