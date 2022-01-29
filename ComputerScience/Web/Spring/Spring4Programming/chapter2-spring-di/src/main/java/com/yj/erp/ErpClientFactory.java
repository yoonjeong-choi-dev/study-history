package com.yj.erp;

import java.util.Properties;

public abstract class ErpClientFactory {
    public static ErpClientFactory instance() {
        Properties props=  new Properties();
        props.setProperty("server", "localhost:7166");
        return instance(props);
    }

    public static ErpClientFactory instance(Properties props) {
        return new DefaultErpClientFactory(props);
    }

    protected ErpClientFactory(){ }

    public abstract ErpClient create();
}
