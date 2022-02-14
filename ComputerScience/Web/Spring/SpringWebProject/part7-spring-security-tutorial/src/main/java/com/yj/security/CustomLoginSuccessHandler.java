package com.yj.security;

import lombok.extern.log4j.Log4j;
import org.springframework.security.core.Authentication;
import org.springframework.security.web.authentication.AuthenticationSuccessHandler;
import org.springframework.security.web.authentication.logout.LogoutSuccessHandler;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

@Log4j
public class CustomLoginSuccessHandler implements AuthenticationSuccessHandler {
    @Override
    public void onAuthenticationSuccess(HttpServletRequest request, HttpServletResponse response,
                                        Authentication authentication) throws IOException, ServletException {
        log.warn("Login Success");

        List<String> roleNames = new ArrayList<>();

        authentication.getAuthorities().forEach(auth -> {
            roleNames.add(auth.getAuthority());
        });

        log.warn("User Role : " + roleNames);

        HttpSession session = request.getSession();

        if(roleNames.contains("ROLE_ADMIN")) {
            session.setAttribute("message", "Redirect to Admin");
            response.sendRedirect("/auth/admin");
            return;
        }

        if(roleNames.contains("ROLE_MEMBER")) {
            session.setAttribute("message", "Redirect to Member");
            response.sendRedirect("/auth/member");
            return;
        }

        session.setAttribute("message", "Redirect to Public");
        response.sendRedirect("/auth/all");
    }
}
