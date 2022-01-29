package com.yj.environmentObject;

import org.springframework.beans.factory.InitializingBean;
import org.springframework.context.EnvironmentAware;
import org.springframework.core.env.Environment;

public class BeanWithEnvironmentAware implements EnvironmentAware, InitializingBean {
    private String driver;
    private String url;
    private String user;
    private String password;

    private Environment environment;

    @Override
    public void setEnvironment(Environment environment) {
        this.environment = environment;
    }

    public void connect() {
        System.out.printf("Driver : %s\nUrl : %s\nUser : %s\nPassword : %s\n", driver, url, user, password);
    }

    @Override
    public void afterPropertiesSet() throws Exception {
        driver = environment.getProperty("db.driver");
        url = environment.getProperty("db.jdbcUrl");
        user = environment.getProperty("db.user");
        password = environment.getProperty("db.password");
    }
}
