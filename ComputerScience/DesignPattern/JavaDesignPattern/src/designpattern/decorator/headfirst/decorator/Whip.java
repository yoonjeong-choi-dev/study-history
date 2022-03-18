package designpattern.decorator.headfirst.decorator;

import designpattern.decorator.headfirst.component.Beverage;

public class Whip extends CondimentDecorator {

    public Whip(Beverage beverage) {
        this.beverage = beverage;
    }

    @Override
    public String getDescription() {
        return beverage.getDescription() + ", Whip Cream";
    }

    @Override
    public double cost() {
        return 0.10 + beverage.cost();
    }
}
