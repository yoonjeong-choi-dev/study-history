package com.yj.factory;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class FactoryConfig {
    @Bean
    public SearchClientFactoryBean myFactory() {
        SearchClientFactoryBean factoryBean = new SearchClientFactoryBean();
        factoryBean.setServer("localhost");
        factoryBean.setPort(7166);
        factoryBean.setEncoding("us_en");
        factoryBean.setContentType("text/html");

        return factoryBean;
    }
}
