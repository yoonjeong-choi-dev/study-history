package designpattern.decorator.headfirst.decorator;

import designpattern.decorator.headfirst.component.Beverage;

public class SteamMilk extends CondimentDecorator {

    public SteamMilk(Beverage beverage) {
        this.beverage = beverage;
    }

    @Override
    public String getDescription() {
        return beverage.getDescription() + ", Steam Milk";
    }

    @Override
    public double cost() {
        return 0.10 + beverage.cost();
    }
}
