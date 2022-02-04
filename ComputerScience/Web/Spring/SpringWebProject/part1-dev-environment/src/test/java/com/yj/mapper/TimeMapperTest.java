package com.yj.mapper;

import lombok.Setter;
import lombok.extern.log4j.Log4j;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit.jupiter.SpringExtension;

@ExtendWith(SpringExtension.class)
@ContextConfiguration("file:src/main/webapp/WEB-INF/spring/root-context.xml")
@Log4j
public class TimeMapperTest {
    @Setter(onMethod_ = { @Autowired})
    private TimeMapper timeMapper;

    @Test
    public void testGetTime() {
        log.info("Sql Mapping Interface Test");
        log.info(timeMapper.getClass().getName());
        log.info(timeMapper.getTime());
    }

    @Test
    public void testGetTimeByXML() {
        log.info("Sql Mapping Interface Test");
        log.info(timeMapper.getClass().getName());
        log.info(timeMapper.getTimeWithXML());
    }
}
