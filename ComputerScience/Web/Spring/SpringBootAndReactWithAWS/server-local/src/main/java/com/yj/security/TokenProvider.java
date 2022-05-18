package com.yj.security;

import com.yj.domain.user.UserEntity;
import io.jsonwebtoken.Claims;
import io.jsonwebtoken.Jwts;
import io.jsonwebtoken.SignatureAlgorithm;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;

import java.util.Date;

@Slf4j
@Service
public class TokenProvider {
    // 토큰 유효 기간 : 3 시간
    private static final long TOKEN_VALIDITY_MILLISECONDS = 3 * 60 * 60 * 1000L;

    @Value("${jwt.secret}")
    private String SECRET_KEY;

    public String create(UserEntity userEntity) {
        // 토큰 발행 시간 및 만료 시간
        Date issuedTime = new Date();
        Date expiredDate = new Date(System.currentTimeMillis() + TOKEN_VALIDITY_MILLISECONDS);

        // 토큰 생성
        return Jwts.builder()
                .signWith(SignatureAlgorithm.HS512, SECRET_KEY)
                .setSubject(userEntity.getId())
                .setIssuer("Todo App")
                .setIssuedAt(issuedTime)
                .setExpiration(expiredDate)
                .compact();
    }

    public String validateAndGetUserId(String token) {
        // Base64 디코딩 후, 서명 알고리즘을 이용하여 토큰 유효성 확인
        // 유효하지 않은 경우 예외 발생
        // 유효한 경우 유저의 아이디 반환
        Claims claims = Jwts.parser()
                .setSigningKey(SECRET_KEY)
                .parseClaimsJws(token)
                .getBody();

        return claims.getSubject();
    }
}
