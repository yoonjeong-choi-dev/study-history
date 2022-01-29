package com.yj.factory;

import com.yj.search.SearchClient;
import com.yj.search.SearchClientFactory;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;

public class MainByFactoryBeanConfig {
    public static void main(String[] args) {

        AnnotationConfigApplicationContext ctx = new AnnotationConfigApplicationContext(FactoryConfig.class);

        SearchClientFactory factory = ctx.getBean("myFactory", SearchClientFactory.class);
        System.out.println(factory);

        SearchClient client = factory.create();
        client.addDocument("Add some html docs");
        client.checkLive();


        SearchClientFactory factory1 = ctx.getBean("myFactory", SearchClientFactory.class);
        System.out.println("factory == factory1 : " + (factory == factory1));



        ctx.close();
    }
}
