package designpattern.decorator.headfirst.decorator;

import designpattern.decorator.headfirst.component.Beverage;

public class SoyMilk extends CondimentDecorator {

    public SoyMilk(Beverage beverage) {
        this.beverage = beverage;
    }

    @Override
    public String getDescription() {
        return beverage.getDescription() + ", Soy Milk";
    }

    @Override
    public double cost() {
        return 0.15 + beverage.cost();
    }
}
