package designpattern.adapter.headfirst.adapter;

import designpattern.adapter.headfirst.Target.Turkey;
import designpattern.adapter.headfirst.adaptee.Duck;

// 기존 Duck 인터페이스를 Turkey 인터페이스로 변환하는 클래스
// Duck 객체를 이용하여 Duck 기능 위임
public class DuckAdapter implements Turkey {
    // 위임할 객체 지정
    private final Duck duck;

    public DuckAdapter(Duck duck) {
        this.duck = duck;
    }

    @Override
    public void gobble() {
        duck.quack();
    }

    @Override
    public void fly() {
        duck.fly();
    }
}
