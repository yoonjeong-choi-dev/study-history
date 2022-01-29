package com.yj.initdestroy;

import javax.annotation.PostConstruct;
import javax.annotation.PreDestroy;

public class WithAnnotation {
    @PostConstruct
    public void init() {
        System.out.println("@PostConstruct init() : Open DB Connection");
    }

    @PreDestroy
    public void destroy() {
        System.out.println("@PreDestroy destroy() : Open DB Connection");
    }

    public void run() {
        System.out.println("WithAnnotation : The bean is running!");
    }

}
