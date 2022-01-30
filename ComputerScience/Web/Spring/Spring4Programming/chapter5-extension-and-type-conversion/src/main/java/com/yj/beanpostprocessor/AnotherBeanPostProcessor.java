package com.yj.beanpostprocessor;

import org.springframework.beans.BeansException;
import org.springframework.beans.factory.config.BeanPostProcessor;
import org.springframework.core.Ordered;
import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;

public class AnotherBeanPostProcessor implements BeanPostProcessor, Ordered {
    private int order;
    @Override
    public int getOrder() {
        return order;
    }

    public void setOrder(int order) {
        this.order = order;
    }

    @Override
    public Object postProcessBeforeInitialization(Object bean, String beanName) throws BeansException {
        return bean;
    }

    @Override
    public Object postProcessAfterInitialization(Object bean, String beanName) throws BeansException {
        // 구현된 인터페이스 정보
        Class<?>[] interfaces = bean.getClass().getInterfaces();
        if (interfaces.length == 0)
            return bean;

        // 각 인터페이스에서 제공하는 메서드(method 인자) 실행될 때, 인터셉트하여 추가 기능 구현
        InvocationHandler handler = new InvocationHandler() {
            @Override
            public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
                long before = System.currentTimeMillis();
                Object result = method.invoke(bean, args);
                long after = System.currentTimeMillis();

                System.out.println("[proxy]" +method.getName() + "의 실행 시간 : " + (after - before));

                return result;
            }
        };
        return Proxy.newProxyInstance(getClass().getClassLoader(), interfaces, handler);
    }


}
