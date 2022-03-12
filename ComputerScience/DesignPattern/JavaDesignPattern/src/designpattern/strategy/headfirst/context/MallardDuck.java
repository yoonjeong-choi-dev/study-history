package designpattern.strategy.headfirst.context;

import designpattern.strategy.headfirst.behavior.FlyWithWings;
import designpattern.strategy.headfirst.behavior.Quack;

public class MallardDuck extends Duck {

    public MallardDuck(String name) {
        super(name);
        flyBehavior = new FlyWithWings();
        quackBehavior = new Quack();
    }

    @Override
    public void display() {
        System.out.printf("I am a mallard duck with name %s\n", name);
    }
}
