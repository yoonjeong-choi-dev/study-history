package com.yj.security;

import lombok.extern.log4j.Log4j;
import org.springframework.security.crypto.password.PasswordEncoder;

@Log4j
public class CustomNoOpsPasswordEncoder implements PasswordEncoder {
    @Override
    public String encode(CharSequence rawPassword) {
        log.warn("Before Encoding : " + rawPassword);

        // 인코딩 처리없이 그래도 반환
        return rawPassword.toString();
    }

    @Override
    public boolean matches(CharSequence rawPassword, String encodedPassword) {
        log.warn("Password Matching - " + rawPassword + " : " + encodedPassword );

        return rawPassword.toString().equals(encodedPassword);
    }
}
