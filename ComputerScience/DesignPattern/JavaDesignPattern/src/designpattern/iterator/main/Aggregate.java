package designpattern.iterator.main;

/**
 *요소들이 나열되어 있는 집합체에 대한 인터페이스
 *  역할
 *      Iterator 역할을 만들어내는 API 결정
 *      자신이 가지고 있는 컬렉션들의 요소를 순서대로 검색하는 객체를 생성하는 역할
 *  구현체는 특정 요소들에 대한 컬렉션을 가지는 클래스
 *  요소들에 대해 순서대로 접근할 수 있는 Iterator 인터페이스를 반환하는 메서드 제공
 */
public interface Aggregate {
    // 특정 컬렌션에 대응하는 Iterator 반환
    Iterator iterator();
}
