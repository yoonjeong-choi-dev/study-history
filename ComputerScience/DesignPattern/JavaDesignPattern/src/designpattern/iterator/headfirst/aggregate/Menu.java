package designpattern.iterator.headfirst.aggregate;

import designpattern.iterator.headfirst.iterator.Iterator;

// Aggregate : 특정 컬렉션을 소유하면서 이터레이터를 생성
// 컬렉션 자체를 관리하는 역할
// => 컬렉션 순회에 대한 역할은 이터레이터에게 위임
public interface Menu {
    Iterator createIterator();
}
