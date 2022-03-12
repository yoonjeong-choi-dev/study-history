package designpattern.strategy.headfirst;

import designpattern.strategy.headfirst.behavior.FlyWithWings;
import designpattern.strategy.headfirst.context.ChickenDuck;
import designpattern.strategy.headfirst.context.Duck;
import designpattern.strategy.headfirst.context.MallardDuck;

public class Main {
    public static void main(String[] args) {
        Duck md = new MallardDuck("MD Duck");
        doDuck(md);

        Duck chicken = new ChickenDuck("Camouflage Duck");
        doDuck(chicken);

        System.out.println("Make the chicken fly!");
        chicken.setFlyBehavior(new FlyWithWings());
        doDuck(chicken);
    }

    private static void doDuck(Duck duck) {
        duck.display();
        duck.fly();
        duck.quack();
        duck.swim();
    }
}
