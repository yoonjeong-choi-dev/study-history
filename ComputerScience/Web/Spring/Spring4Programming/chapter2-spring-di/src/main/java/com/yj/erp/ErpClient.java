package com.yj.erp;

public interface ErpClient {
    public void connect();

    public void close();

    public void sendPurchaseInfo(ErpOrderData oi);
}
