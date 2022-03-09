package designpattern.iterator.headfirst.iterator;

// 컬렉션의 순회를 담당하는 인터페이스
public interface Iterator {
    boolean hasNext();
    Object next();
}
