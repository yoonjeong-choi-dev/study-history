package com.yj.di;

import lombok.Setter;
import lombok.extern.log4j.Log4j;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import static org.junit.jupiter.api.Assertions.*;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit.jupiter.SpringExtension;


@ExtendWith(SpringExtension.class)
@ContextConfiguration("file:src/main/webapp/WEB-INF/spring/root-context.xml")
@Log4j
class RestaurantTest {
    @Setter(onMethod_ = { @Autowired})
    private Restaurant restaurant;

    @Test
    public void testExist() {
        assertNotNull(restaurant);

        log.info("세터 및 autowired 를 이용한 의존성 주입 테스트");
        log.info("Restaurant : " + restaurant);
        log.info("Restaurant.chef : " + restaurant.getChef());
    }
}