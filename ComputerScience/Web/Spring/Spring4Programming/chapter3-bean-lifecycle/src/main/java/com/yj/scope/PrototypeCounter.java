package com.yj.scope;

public class PrototypeCounter {
    static int count = 0;

    public PrototypeCounter() {
        count++;
    }

    public void info() {
        System.out.printf("This instance is %d-th\n", count);
    }
}
