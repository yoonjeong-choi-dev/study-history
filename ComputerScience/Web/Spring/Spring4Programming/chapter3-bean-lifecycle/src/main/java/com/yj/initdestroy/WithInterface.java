package com.yj.initdestroy;

import org.springframework.beans.factory.DisposableBean;
import org.springframework.beans.factory.InitializingBean;

public class WithInterface implements InitializingBean, DisposableBean {
    @Override
    public void destroy() throws Exception {
        System.out.println("Destroy the bean : Close DB Connection");
    }

    @Override
    public void afterPropertiesSet() throws Exception {
        System.out.println("Initialize the bean : Open DB Connection");
    }

    public void run() {
        System.out.println("WithInterface: The bean is running!");
    }
}
