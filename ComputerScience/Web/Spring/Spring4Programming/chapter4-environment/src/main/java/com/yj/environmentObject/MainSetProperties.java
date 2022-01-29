package com.yj.environmentObject;

import org.springframework.context.ConfigurableApplicationContext;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.core.env.ConfigurableEnvironment;
import org.springframework.core.env.MutablePropertySources;
import org.springframework.core.io.support.ResourcePropertySource;

import java.io.IOException;

public class MainSetProperties {
    public static void main(String[] args) {
        ConfigurableApplicationContext ctx = new AnnotationConfigApplicationContext();
        ConfigurableEnvironment env = ctx.getEnvironment();
        MutablePropertySources propertySources = env.getPropertySources();

        try {
            propertySources.addLast(new ResourcePropertySource("classpath:db.properties"));
            String[] props = {"db.driver", "db.jdbcUrl", "db.user", "db.password"};
            for(String key : props) {
                System.out.printf("%s : %s\n", key, env.getProperty(key));
            }

        } catch ( IOException ex) {
            System.out.println(ex.getMessage());
        }
    }
}
