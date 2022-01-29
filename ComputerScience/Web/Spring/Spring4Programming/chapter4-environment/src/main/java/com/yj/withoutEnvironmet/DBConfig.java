package com.yj.withoutEnvironmet;


import org.springframework.context.annotation.Bean;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.PropertySource;
import org.springframework.context.support.PropertySourcesPlaceholderConfigurer;
import org.springframework.core.io.ClassPathResource;

@Configuration
@PropertySource("classpath:/db.properties")
public class DBConfig {
    // 프로퍼티 파일 로드
    @Bean
    public static PropertySourcesPlaceholderConfigurer properites() {
        PropertySourcesPlaceholderConfigurer configurer = new PropertySourcesPlaceholderConfigurer();
        // configurer.setLocation(new ClassPathResource("db.properties"));
        return configurer;
    }

    @Value("${db.driver}")
    private String driver;
    @Value("${db.jdbcUrl}")
    private String jdbcUrl;
    @Value("${db.user}")
    private String user;
    @Value("${db.password}")
    private String password;

    @Bean(initMethod = "init")
    public DBConnection myConn() {
        DBConnection conn = new DBConnection();
        conn.setDriver(driver);
        conn.setUrl(jdbcUrl);
        conn.setUser(user);
        conn.setPassword(password);
        return conn;
    }
}
