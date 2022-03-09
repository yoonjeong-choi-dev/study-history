package designpattern.adapter.headfirst.adapter;

import java.util.Enumeration;
import java.util.Iterator;

// 기존 Enumeration 인터페이스를 Iterator 인터페이스로 변환하는 클래스
public class EnumerationIterator<T> implements Iterator<T> {
    private final Enumeration<T> enumeration;

    public EnumerationIterator(Enumeration<T> enumeration) {
        this.enumeration = enumeration;
    }

    @Override
    public boolean hasNext() {
        return enumeration.hasMoreElements();
    }

    @Override
    public T next() {
        return enumeration.nextElement();
    }

    @Override
    public void remove() {
        throw new UnsupportedOperationException();
    }
}
