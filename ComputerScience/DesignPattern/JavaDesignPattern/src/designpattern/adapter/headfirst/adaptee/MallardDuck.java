package designpattern.adapter.headfirst.adaptee;

public class MallardDuck implements Duck {

    @Override
    public void quack() {
        System.out.println("Quack!");
    }

    @Override
    public void fly() {
        System.out.println("Fly over the river!");
    }
}
