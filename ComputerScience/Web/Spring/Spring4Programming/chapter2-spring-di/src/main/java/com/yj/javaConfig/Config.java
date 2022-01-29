package com.yj.javaConfig;

import com.yj.auth.*;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

import java.util.Arrays;

@Configuration
public class Config {
    @Bean
    public User user1() {
        return new User("yjchoi", "1234");
    }

    @Bean(name="user2")
    public User someUser() {
        return new User("yoonjeong", "1111");
    }

    @Bean
    public UserRepository userRepository() {
        UserRepository userRepo = new UserRepository();
        userRepo.setUsers(Arrays.asList(user1(), someUser()));
        return userRepo;
    }

    @Bean
    public AuthFailLogger authFailLogger() {
        AuthFailLogger logger = new AuthFailLogger();
        logger.setThreshold(2);
        return logger;
    }

    @Bean
    public PasswordChangeService changePwService() {
        return new PasswordChangeService(userRepository());
    }

    @Bean
    public AuthenticationService authenticationService() {
        AuthenticationService svc = new AuthenticationService();
        svc.setFailLogger(authFailLogger());
        svc.setUserRepository(userRepository());
        return svc;
    }
}
