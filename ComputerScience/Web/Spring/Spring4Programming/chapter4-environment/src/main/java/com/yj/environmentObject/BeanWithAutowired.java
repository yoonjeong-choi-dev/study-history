package com.yj.environmentObject;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.core.env.Environment;

import javax.annotation.PostConstruct;

public class BeanWithAutowired {
    private String driver;
    private String url;
    private String user;
    private String password;

    @Autowired
    private Environment environment;

    @PostConstruct
    public void init() {
        driver = environment.getProperty("db.driver");
        url = environment.getProperty("db.jdbcUrl");
        user = environment.getProperty("db.user");
        password = environment.getProperty("db.password");
    }

    public void connect() {
        System.out.printf("Driver : %s\nUrl : %s\nUser : %s\nPassword : %s\n", driver, url, user, password);
    }
}
