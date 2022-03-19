package designpattern.composite.headfirst;

import java.util.Iterator;

/**
 * Component 역할 클래스
 * - Composite 역할과 Leaf 역할을 동일시 하기 위한 인터페이스(API) 제공
 * - 위 두 역할에 대해서 동일한 메서드를 호출 가능하도록 만드는 컴포지트 패턴의 주요 역할
 * - Composite 역할과 Leaf 역할에 대해서 불필요한 메서드들이 존재
 * => 자신의 역할에 맞지 않는 메서드에 대해서 오버라이드를 하지 않으면 예외를 발생하는 기본 메서드 정의
 */
public abstract class MenuComponent {
    public void add(MenuComponent menuComponent) {
        throw new UnsupportedOperationException();
    }

    public void remove(MenuComponent menuComponent) {
        throw new UnsupportedOperationException();
    }

    public MenuComponent getChild(int i) {
        throw new UnsupportedOperationException();
    }

    public String getName() {
        throw new UnsupportedOperationException();
    }

    public String getDescription() {
        throw new UnsupportedOperationException();
    }

    public double getPrice() {
        throw new UnsupportedOperationException();
    }

    public boolean isVegetarian() {
        throw new UnsupportedOperationException();
    }

    public abstract Iterator<MenuComponent> createIterator();

    public void print() {
        throw new UnsupportedOperationException();
    }
}
