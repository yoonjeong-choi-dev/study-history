package com.yj.environmentObject;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.PropertySource;

@Configuration
@PropertySource("classpath:/db.properties")
public class DBConfig {
    @Bean
    public BeanWithEnvironmentAware db1() {
        return new BeanWithEnvironmentAware();
    }

    @Bean
    public BeanWithAutowired db2() {
        return new BeanWithAutowired();
    }
}
