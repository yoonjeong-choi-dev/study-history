package designpattern.templatemethod.headfirst;

import designpattern.templatemethod.headfirst.abstractclass.CaffeineBeverage;
import designpattern.templatemethod.headfirst.abstractclass.CaffeineBeverageWithHook;
import designpattern.templatemethod.headfirst.concrete.Coffee;
import designpattern.templatemethod.headfirst.concrete.CoffeeWithHook;
import designpattern.templatemethod.headfirst.concrete.Tea;

public class BeverageMain {
    public static void main(String[] args) {
        System.out.println("==========================");
        System.out.println("Example 1 : Simple Template Method");
        CaffeineBeverage tea = new Tea();
        CaffeineBeverage coffee = new Coffee();

        tea.prepareRecipe();
        coffee.prepareRecipe();

        System.out.println("==========================");
        System.out.println("Example 2 :Template Method With Hook");
        CaffeineBeverageWithHook coffeeWithHook = new CoffeeWithHook();
        coffeeWithHook.prepareRecipe();
    }
}
