package com.yj.initdestroy;


public class WithCustom {
    public void customInit() {
        System.out.println("customInit() : Open DB Connection");
    }

    public void customDestroy() {
        System.out.println("customDestroy() : Open DB Connection");
    }

    public void run() {
        System.out.println("WithCustom : The bean is running!");
    }
}
