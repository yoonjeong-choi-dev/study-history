package com.yj.di;

import lombok.Setter;
import lombok.extern.log4j.Log4j;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit.jupiter.SpringExtension;

import static org.junit.jupiter.api.Assertions.*;

@ExtendWith(SpringExtension.class)
@ContextConfiguration("file:src/main/webapp/WEB-INF/spring/root-context.xml")
@Log4j
class HotelTest {
    @Setter(onMethod_ = { @Autowired})
    private Hotel hotel;

    @Test
    public void testExist() {
        assertNotNull(hotel);
        assertNotNull(hotel.getChef());

        log.info("생성자를 이용한 의존성 주입 테스트");
        log.info("Hotel : " + hotel);
        log.info("Hotel.chef : " + hotel.getChef());
    }
}