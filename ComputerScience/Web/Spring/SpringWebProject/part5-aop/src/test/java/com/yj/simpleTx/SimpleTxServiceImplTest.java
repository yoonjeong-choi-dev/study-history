package com.yj.simpleTx;


import lombok.Setter;
import lombok.extern.log4j.Log4j;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.support.DefaultListableBeanFactory;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit.jupiter.SpringExtension;

import static org.junit.jupiter.api.Assertions.*;

@ExtendWith(SpringExtension.class)
@ContextConfiguration("file:src/main/webapp/WEB-INF/spring/root-context.xml")
@Log4j
class SimpleTxServiceImplTest {
    @Setter(onMethod_ = {@Autowired})
    private DefaultListableBeanFactory bf;

    @Setter(onMethod_ = {@Autowired})
    private SimpleTxService service;

    private String testStr = "Final Fantasy XIII-2 is a 2011 role-playing video game developed and published by Square Enix. XIII-2 is a direct sequel to the 2009 role-playing game Final Fantasy XIII and part of the Fabula Nova Crystallis subseries. Development of the game began in early 2010 and involved many of the key designers from the previous game. It includes modified features from the previous game, including fast-paced combat and a customizable \"Paradigm\" system";

    @Test
    public void testServiceExist() {
        String[] names = bf.getBeanDefinitionNames();
        for(String name : names) {
            if(bf.getBean(name).getClass().isAssignableFrom(SimpleTxService.class)) {
                log.info("Bean name : " + name);
                log.info("Bean Object : " + bf.getBean(name));
                log.info("Bean Class : " + bf.getBean(name).getClass().getName());
                log.info("=======================================");
            }
        }

        log.info("Service : " + service);
    }

    @Test
    public void addData() {
        log.info("Test String size : " + testStr.getBytes().length);

        service.addData(testStr);
    }

    @Test
    public void addDataWithTx() {
        log.info("Test String size : " + testStr.getBytes().length);
        service.addDataTx(testStr);
    }
}