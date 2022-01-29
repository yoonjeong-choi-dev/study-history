package com.yj.factory;

import com.yj.erp.ErpClient;
import com.yj.erp.ErpClientFactory;
import org.springframework.context.support.GenericXmlApplicationContext;

public class MainByStaticXML {
    public static void main(String[] args) {
        GenericXmlApplicationContext ctx = new GenericXmlApplicationContext("classpath:factory-static.xml");
        ErpClientFactory factory = ctx.getBean("factory", ErpClientFactory.class);
        ErpClient client = factory.create();

        client.connect();
        client.close();

        ctx.close();
    }
}
