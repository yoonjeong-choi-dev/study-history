package com.yj.security;

import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.security.authentication.AbstractAuthenticationToken;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.authority.AuthorityUtils;
import org.springframework.security.core.context.SecurityContext;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.web.authentication.WebAuthenticationDetailsSource;
import org.springframework.stereotype.Component;
import org.springframework.util.StringUtils;
import org.springframework.web.filter.OncePerRequestFilter;

import javax.servlet.FilterChain;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

// 스프링 시큐리티에서 생성하는 필터 체인에 등록할 필터 정의
// 스프링 시큐리티에서 생성된 필터 체인은 서블릿 컨테이너가 관리하는 필터 체인 내부로 등록됨
@Slf4j
@RequiredArgsConstructor
@Component
public class JWTAuthenticationFilter extends OncePerRequestFilter {

    private static final String AUTHORIZATION_HEADER = "Authorization";
    private static final String AUTHORIZATION_VALUE_START_WITH = "Bearer ";

    private final TokenProvider tokenProvider;

    @Override
    protected void doFilterInternal(HttpServletRequest request, HttpServletResponse response, FilterChain filterChain)
            throws ServletException, IOException {

        log.info("Token Filter is running...");
        try {
            // HTTP 요청을 통해 토큰 정보 파싱
            final String token = parseBearerToken(request);

            if (token != null && !token.equalsIgnoreCase("null")) {
                // 토큰이 유효한 경우
                String userId = tokenProvider.validateAndGetUserId(token);
                log.info("Authenticated User Id : " + userId);

                // 스프링 시큐리티에서 제공하는 토큰 생성 및 요청 정보를 토큰에 저장
                AbstractAuthenticationToken authenticationToken = new UsernamePasswordAuthenticationToken(
                        userId,
                        null,
                        AuthorityUtils.NO_AUTHORITIES
                );
                authenticationToken.setDetails(new WebAuthenticationDetailsSource().buildDetails(request));

                // 스프링 시큐리티 컨텍스트에 현재 요청 유저 정보를 포함한 요청 정보 등록
                // => 이후 스프링 어플리케이션에서 해당 정보 이용 가능
                // 등록은 현재 스레드의 메모리에 정보를 저장하는 것으로, 동일 스레드에서만 접근 가능
                // 스프링 컨트롤러 메서드 인자로 @AuthenticationPrincipal 추가하여 사용 가능
                SecurityContext securityContext = SecurityContextHolder.createEmptyContext();
                securityContext.setAuthentication(authenticationToken);
                SecurityContextHolder.setContext(securityContext);
            }
        } catch (Exception e) {
            log.warn("Could not set user authentication in spring security context : {}", e.getMessage());
        }

        filterChain.doFilter(request, response);
    }

    // 토큰 기반 인증의 경우 Authorization 헤더가 Bearer 로 시작
    private String parseBearerToken(HttpServletRequest request) {
        String authHeaderValue = request.getHeader(AUTHORIZATION_HEADER);

        if (StringUtils.hasText(authHeaderValue) && authHeaderValue.startsWith(AUTHORIZATION_VALUE_START_WITH)) {
            return authHeaderValue.substring(AUTHORIZATION_VALUE_START_WITH.length());
        } else {
            log.info("Token is invalid : check 'Authorization' header");
            return null;
        }
    }
}
