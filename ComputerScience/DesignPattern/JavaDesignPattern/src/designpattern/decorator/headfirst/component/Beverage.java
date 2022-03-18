package designpattern.decorator.headfirst.component;

/**
 * 장식할 대상(내용물)을 표현하는 인터페이스
 * - 장식 클래스는 해당 인터페이스를 상속받아 내용물과 장식을 동일시 함
 */
public interface Beverage {
    String getDescription();
    double cost();
}
