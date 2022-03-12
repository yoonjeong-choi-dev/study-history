package designpattern.strategy.headfirst.behavior;

public class FlyWithWings implements FlyBehavior{
    @Override
    public void fly() {
        System.out.println("I am flying with my flies~~~");
    }
}
