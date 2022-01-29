package com.yj.factory;

import com.yj.search.SearchClient;
import com.yj.search.SearchClientFactory;
import org.springframework.context.support.GenericXmlApplicationContext;

public class MainByFactoryBeanXml {
    public static void main(String[] args) {
        GenericXmlApplicationContext ctx = new GenericXmlApplicationContext("classpath:factory-bean.xml");

        SearchClientFactory factory = ctx.getBean("factory", SearchClientFactory.class);
        System.out.println(factory);

        SearchClient client = factory.create();
        client.addDocument("Add some json docs");
        client.checkLive();


        SearchClientFactory factory1 = ctx.getBean("factory", SearchClientFactory.class);
        System.out.println("factory == factory1 : " + (factory == factory1));



        ctx.close();
    }
}
