package com.yj;

import org.springframework.context.support.AbstractApplicationContext;
import org.springframework.context.support.GenericXmlApplicationContext;

public class MainWithSpring {
    public static void main(String[] args) {
        String configLocation = "classpath:applicationContext.xml";

        AbstractApplicationContext ctx = new GenericXmlApplicationContext(configLocation);

        Project project = ctx.getBean("sampleProject", Project.class);
        project.build();

        ctx.close();
    }
}
