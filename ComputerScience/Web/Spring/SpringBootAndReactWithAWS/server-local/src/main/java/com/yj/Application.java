package com.yj;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

// 스프링부트를 설정하는 클래스임을 나타내는 어노테이션
// => 스프링은 해당 어노테이션이 있는 클래스의 패키지를 베이스 패키지로 간주
// => 스프링은 베이스 패키지 및 하위 패키지에서 자바 빈을 찾아 해당 빈들을 의존성 주입의 대상을 간주
// => 어플리케이션을 위한 객체들을 관리하는 최상위 패키지에 해당
// @ComponentScan 을 포함하고 있어, 하위 패키지에서 @Component 어노테이션을 사용하기만 하면 스프링 빈으로 등록 됨
@SpringBootApplication
public class Application {
    public static void main(String[] args) {
        // SpringApplication.run 메서드를 통해 내장 WAS 실행
        SpringApplication.run(Application.class, args);
    }
}
