package com.yj.xmlConfig;

import com.yj.auth.AuthException;
import com.yj.auth.AuthenticationService;
import com.yj.auth.PasswordChangeService;
import com.yj.auth.UserNotFoundException;
import org.springframework.context.support.GenericXmlApplicationContext;

public class MainByXML {
    public static void main(String[] args) {
        GenericXmlApplicationContext ctx = new GenericXmlApplicationContext("classpath:config.xml");

        AuthenticationService authService = (AuthenticationService) ctx.getBean("authenticationService");

        runAuthAndCatchEx(authService, "yjchoi", "1234");
        runAuthAndCatchEx(authService, "yjchoi", "1111");
        runAuthAndCatchEx(authService, "yjchoi", "1111");
        runAuthAndCatchEx(authService, "yjchoi", "1111");
        runAuthAndCatchEx(authService, "yjchoi", "1111");
        runAuthAndCatchEx(authService, "yjchoi", "1111");

        try {
            authService.authenticate("yjchoi123", "1234");
        } catch (UserNotFoundException ex) {
            System.out.println("User not found");
        }

        PasswordChangeService passwordChangeService = (PasswordChangeService) ctx.getBean("changePwService");
        passwordChangeService.changePassword("yoonjeong", "1111","1234");
        runAuthAndCatchEx(authService, "yoonjeong", "1234");
        runAuthAndCatchEx(authService, "yoonjeong", "1111");
        ctx.close();

    }

    private static void runAuthAndCatchEx(AuthenticationService svc, String userId, String password) {
        try {
            svc.authenticate(userId, password);
        } catch (AuthException ex) {

        }
    }


}
