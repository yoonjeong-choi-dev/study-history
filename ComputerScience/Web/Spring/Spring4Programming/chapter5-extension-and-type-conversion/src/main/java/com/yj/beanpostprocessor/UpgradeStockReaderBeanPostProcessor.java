package com.yj.beanpostprocessor;

import org.springframework.beans.BeansException;
import org.springframework.beans.factory.config.BeanPostProcessor;
import org.springframework.core.Ordered;

public class UpgradeStockReaderBeanPostProcessor implements BeanPostProcessor, Ordered {
    @Override
    public Object postProcessBeforeInitialization(Object bean, String beanName) throws BeansException {
        // 객체 생성 ~ 초기화 사이에는 아무 작업 X
        return bean;
    }

    @Override
    public Object postProcessAfterInitialization(Object bean, String beanName) throws BeansException {
        // StockReader 구현체인 경우, 확장 클래스로 변경
        if(StockReader.class.isAssignableFrom(bean.getClass())) {
            return new UpgradeStockReader((StockReader) bean);
        } else {
            return bean;
        }
    }

    private int order;
    @Override
    public int getOrder() {
        return order;
    }

    public void setOrder(int order) {
        this.order = order;
    }
}
