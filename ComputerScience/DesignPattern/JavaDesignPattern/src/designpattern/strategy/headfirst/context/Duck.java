package designpattern.strategy.headfirst.context;

import designpattern.strategy.headfirst.behavior.FlyBehavior;
import designpattern.strategy.headfirst.behavior.QuackBehavior;

// 전략을 사용하는 컨텍스트 역할
// 전략 인터페이스를 필드로 가지며, 특정 기능을 전략 인터페이스에게 위임
public abstract class Duck {
    protected final String name;

    protected FlyBehavior flyBehavior;
    protected QuackBehavior quackBehavior;

    public Duck(String name) {
        this.name = name;
    }

    public void setFlyBehavior(FlyBehavior flyBehavior) {
        this.flyBehavior = flyBehavior;
    }

    public void setQuackBehavior(QuackBehavior quackBehavior) {
        this.quackBehavior = quackBehavior;
    }

    public final void fly() {
        flyBehavior.fly();
    }

    public final void quack() {
        quackBehavior.quack();
    }

    public void swim() {
        System.out.printf("%s is swimming~\n", name);
    }

    public abstract void display();
}
