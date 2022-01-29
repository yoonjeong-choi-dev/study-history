package com.yj.autowired;


import com.yj.auth.User;
import com.yj.search.SearchClient;
import com.yj.search.SearchClientFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;

public class FactoryService {
    private SearchClientFactory factory;


    @Autowired
    public void setFactory(SearchClientFactory factory) {
        this.factory = factory;
    }

    public void testFactory() {
        System.out.println(factory);

        SearchClient client = (SearchClient) factory.create();
        client.addDocument("Add some html docs");
        client.checkLive();
    }

    @Autowired
    @Qualifier("someUser")
    private User user;

    public void testQualifier() {
        System.out.println(user);
    }
}
