package designpattern.decorator.headfirst;

import designpattern.decorator.headfirst.component.Beverage;
import designpattern.decorator.headfirst.component.Espresso;
import designpattern.decorator.headfirst.component.HouseBlend;
import designpattern.decorator.headfirst.decorator.Mocha;
import designpattern.decorator.headfirst.decorator.Whip;

public class Main {
    public static void main(String[] args) {
        Beverage beverage = new Espresso();
        printBeverage(beverage);

        Beverage beverage2 = new HouseBlend();
        beverage2 = new Mocha(new Mocha(new Whip(beverage2)));
        printBeverage(beverage2);
    }

    private static void printBeverage(Beverage beverage) {
        System.out.printf("%s : $%.2f\n", beverage.getDescription(), beverage.cost());
    }
}
