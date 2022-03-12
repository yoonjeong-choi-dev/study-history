package designpattern.prototype.main.framework;

/**
 * Prototype 역할을 하는 인터페이스
 * - Cloneable 인터페이스를 상속받아 객체 복사 메서드인 clone 사용
 * - 프로토타입 패턴을 이용하여 복제시킬 객체들이 구현해야 하는 인터페이스 정의
 */
public interface Product extends Cloneable {
    void use(String s);

    Product createClone();
}
