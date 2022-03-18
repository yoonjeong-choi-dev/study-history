package designpattern.decorator.headfirst.decorator;

import designpattern.decorator.headfirst.component.Beverage;

/**
 * 장식에 해당하는 추상 클래스
 * - 장식 대상 객체를 참조 변수로 가짐
 * - 장식 대상과 관련된 역할은 해당 대상에게 위임
 * - 장식 대상에 해당하는 인터페이스(Beverage)를 구현하여 내용물과 장식을 동일시
 */
public abstract class CondimentDecorator implements Beverage {
    protected Beverage beverage;
}
