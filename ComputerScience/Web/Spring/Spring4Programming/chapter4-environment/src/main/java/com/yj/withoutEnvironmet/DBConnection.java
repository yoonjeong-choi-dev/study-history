package com.yj.withoutEnvironmet;

public class DBConnection {
    private String driver;
    private String url;
    private String user;
    private String password;

    public void setDriver(String driver) {
        this.driver = driver;
    }

    public void setUrl(String url) {
        this.url = url;
    }

    public void setUser(String user) {
        this.user = user;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public void init() {
        System.out.printf("Connect to... %s with user %s by the driver %s\n", url, user, driver);
    }

    public void connect() {
        System.out.printf("Driver : %s\nUrl : %s\nUser : %s\nPassword : %s\n", driver, url, user, password);
    }
}
