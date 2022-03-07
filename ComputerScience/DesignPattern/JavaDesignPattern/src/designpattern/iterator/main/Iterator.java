package designpattern.iterator.main;

/**
 *컬렌션의 요소를 순서대로 접근하기 위한 루프 변수와 같은 역할 수행
 *  역할 : 요소를 순서대로 검색하기 위한 API
 *  Aggregate 인터페이스에서 생성
 *  특정 요소에 접근하기 위한 인덱스 변수에 대한 추상화
 *  구현체를 통해 탐색 순서 지정 가능
 */
public interface Iterator {
    // 다음 요소의 존재 여부 확인
    boolean hasNext();

    // 다음 요소 반환
    Object next();
}
