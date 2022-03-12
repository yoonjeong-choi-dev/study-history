package designpattern.strategy.headfirst.behavior;

public class Quack implements QuackBehavior {
    @Override
    public void quack() {
        System.out.println("Quack! Quack!");
    }
}
