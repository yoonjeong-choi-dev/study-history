package designpattern.templatemethod.headfirst.concrete;

import designpattern.templatemethod.headfirst.abstractclass.CaffeineBeverage;

public class Tea extends CaffeineBeverage {
    @Override
    protected void init() {
        System.out.println("Preparing Tee...");
    }

    @Override
    protected void brew() {
        System.out.println("Brewing tea");
    }

    @Override
    protected void addCondiments() {
        System.out.println("Adding lemon to the tea");
    }
}
