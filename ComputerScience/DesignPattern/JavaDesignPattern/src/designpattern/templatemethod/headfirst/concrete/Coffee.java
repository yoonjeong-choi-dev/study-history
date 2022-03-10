package designpattern.templatemethod.headfirst.concrete;

import designpattern.templatemethod.headfirst.abstractclass.CaffeineBeverage;

public class Coffee extends CaffeineBeverage {
    @Override
    protected void init() {
        System.out.println("Preparing Coffee...");
    }

    @Override
    protected void brew() {
        System.out.println("Brewing coffee grinds through the filter");
    }

    @Override
    protected void addCondiments() {
        System.out.println("Adding sugar and milk to the coffee");
    }
}
