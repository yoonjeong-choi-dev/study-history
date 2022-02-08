package com.yj.simpleAop;

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
public class SampleServiceTest {
    @Setter(onMethod_ = {@Autowired})
    private SampleService service;

    @Test
    public void testClass() {
        log.info("Check the proxy of Target object");
        log.info(service);
        log.info(service.getClass().getName());
    }

    @Test
    public void testAop() throws Exception {
        log.info(service.doAdd("123", "123"));
    }

    @Test
    public void testException() throws Exception {
        log.info(service.doAdd("123", "abc"));
    }

    @Test
    public void testAround() throws Exception{
        log.info("Example 1");
        log.info(service.doMinus("123", "100"));

        log.info("Example 2");
        log.info(service.doMinus("123", "abc"));
    }
}
