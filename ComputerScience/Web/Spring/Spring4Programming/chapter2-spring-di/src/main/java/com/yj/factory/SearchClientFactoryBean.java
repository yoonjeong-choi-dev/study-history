package com.yj.factory;

import com.yj.search.SearchClientFactory;
import com.yj.search.SearchClientFactoryBuilder;
import org.springframework.beans.factory.FactoryBean;

public class SearchClientFactoryBean implements FactoryBean<SearchClientFactory> {
    private SearchClientFactory factory;

    private String server;
    private int port;
    private String contentType;
    private String encoding = "utf8";

    // 프로퍼티 정의
    public void setServer(String server) {
        this.server = server;
    }

    public void setPort(int port) {
        this.port = port;
    }

    public void setContentType(String contentType) {
        this.contentType = contentType;
    }

    public void setEncoding(String encoding) {
        this.encoding = encoding;
    }

    // 인터페이스 구현
    @Override
    public SearchClientFactory getObject() throws Exception {
        if(factory != null) return factory;

        SearchClientFactoryBuilder builder = new SearchClientFactoryBuilder();
        builder.server(server).port(port).contentType(contentType == null ? "json" : contentType).encoding(encoding);

        SearchClientFactory clientFactory = builder.build();
        clientFactory.init();

        factory = clientFactory;
        return factory;
    }

    @Override
    public Class<?> getObjectType() {
        return SearchClientFactory.class;
    }

    @Override
    public boolean isSingleton() {
        return true;
    }
}
