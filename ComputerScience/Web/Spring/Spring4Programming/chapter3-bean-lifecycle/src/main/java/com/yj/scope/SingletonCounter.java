package com.yj.scope;

public class SingletonCounter {
    static int count = 0;

    public SingletonCounter() {
        count++;
    }

    public void info() {
        System.out.printf("This instance is %d-th\n", count);
    }
}
