package designpattern.visitor.main.element;

import designpattern.visitor.main.visitor.Visitor;

/**
 * 방문자 클래스(Visitor)가 방문하는 구현체의 인터페이스
 * - 방문자 클래스의 방문을 요청하는 API 제공
 * - 구현체는 인자로 받은 방문자 클래스에게 처리(visitor.visit) 요청
 */
public interface Element {
    void accept(Visitor visitor);
}
