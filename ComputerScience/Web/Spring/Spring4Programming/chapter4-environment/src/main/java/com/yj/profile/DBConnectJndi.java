package com.yj.profile;

public class DBConnectJndi implements DBConnect {
    private String jndi;

    public void setJndi(String jndi) {
        this.jndi = jndi;
    }

    public void init() {
        System.out.printf("Connect to... %s via JNDI\n", jndi);
    }

    @Override
    public void connect() {
        System.out.println("Success to Connect");
    }
}
