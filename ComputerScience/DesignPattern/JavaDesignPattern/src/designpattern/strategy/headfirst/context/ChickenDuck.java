package designpattern.strategy.headfirst.context;

import designpattern.strategy.headfirst.behavior.FlyNoWay;
import designpattern.strategy.headfirst.behavior.Squeak;

public class ChickenDuck extends Duck {

    public ChickenDuck(String name) {
        super(name);
        flyBehavior = new FlyNoWay();
        quackBehavior = new Squeak();
    }

    @Override
    public void display() {
        System.out.printf("I am actually a chicken... with name %s\n", name);
    }
}
