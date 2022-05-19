package com.yj.config;

import com.yj.security.JWTAuthenticationFilter;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;

import org.springframework.context.annotation.Bean;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.config.annotation.web.configuration.WebSecurityConfigurerAdapter;
import org.springframework.security.config.http.SessionCreationPolicy;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.web.filter.CorsFilter;


@Slf4j
@RequiredArgsConstructor
@EnableWebSecurity
public class WebSecurityConfig extends WebSecurityConfigurerAdapter {
    private final JWTAuthenticationFilter authenticationFilter;

    @Bean
    public PasswordEncoder passwordEncoder() {
        return new BCryptPasswordEncoder();
    }

    @Override
    protected void configure(HttpSecurity httpSecurity) throws Exception {
        // API 서버 => cors 설정 및 csrf 토큰 비활성화
        httpSecurity
                .httpBasic().disable()
                .cors().and().csrf().disable();

        // 시큐리티가 제공하는 기본 로그인/로그아웃 및 세션 비활성화
        httpSecurity.logout().disable()
                .sessionManagement().sessionCreationPolicy(SessionCreationPolicy.STATELESS);

        // 접근 권한 설정 : 토큰 발급 요청은 허용
        httpSecurity.authorizeRequests()
                .antMatchers("/", "/auth/**").permitAll()
                .antMatchers("/error").permitAll()
                .anyRequest().authenticated();

        // CORS 필터 실행 후 실행할 인증 관련 필터 등록
        httpSecurity.addFilterAfter(authenticationFilter, CorsFilter.class);
    }
}
