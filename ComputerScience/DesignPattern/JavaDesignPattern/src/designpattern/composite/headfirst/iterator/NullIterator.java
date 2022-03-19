package designpattern.composite.headfirst.iterator;

import designpattern.composite.headfirst.MenuComponent;

import java.util.Iterator;

/**
 * leaf 역할의 객체의 경우 단일 객체
 * - 순회할 대상이 없음
 * - 클라이언트 측에서 일관된 이터레이터 패턴을 적용하기 위해 무조건 false를 반환하는 hasNext 정의
 */
public class NullIterator implements Iterator<MenuComponent> {

    @Override
    public boolean hasNext() {
        return false;
    }

    @Override
    public MenuComponent next() {
        return null;
    }
}
