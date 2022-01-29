package com.yj.erp;

import java.util.Properties;

public class DefaultErpClientFactory extends ErpClientFactory {
    private String server;

    public DefaultErpClientFactory(Properties props) {
        this.server = props.getProperty("server");
    }

    @Override
    public ErpClient create() {
        return new ErpClient() {
            @Override
            public void connect() {
                System.out.println("Connected : " + server);
            }

            @Override
            public void close() {
                System.out.println("Closed : " + server);
            }

            @Override
            public void sendPurchaseInfo(ErpOrderData oi) {
                System.out.println("주문 정보 전송 : " + server);
            }
        };
    }
}
