package designpattern.factorymethod.main.framework;

/**
 * Factory 추상 클래스에서 생성할 객체에 해당하는 추상 클래스
 * - 생성되어야 하는 인스턴스가 가여야 하는 인터페이스를 정의
 * - 구체적인 객체의 내용은 하위 클래스에서 구현함으로써 생성할 객체에 대한 추상화
 */
public abstract class Product {
    public abstract void use();
}
