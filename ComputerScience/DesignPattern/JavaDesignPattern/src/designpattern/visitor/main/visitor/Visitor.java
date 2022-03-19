package designpattern.visitor.main.visitor;

import designpattern.visitor.main.element.Directory;
import designpattern.visitor.main.element.File;

/**
 * Visitor 패턴에서 각 요소에 대한 처리를 추상화한 추상 클래스
 * - 추상화된 데이터 구조를 순회하는 상황에서, 각 요소에 대한 처리를 담당
 * - 처리에 대한 API 제공
 * - 처리 로직은 방문하는 대상의 데이터 구조에 의존
 */
public abstract class Visitor {
    public abstract void visit(File file);
    public abstract void visit(Directory directory);
}
