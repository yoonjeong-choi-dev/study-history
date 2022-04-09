package designpattern.interpreter.main.exercise.language;

import designpattern.interpreter.main.exercise.facade.Executor;

/**
 * Abstract Expression 역할
 * - 파싱된 구문 트리를 구성하는 노드의 공통 인터페이스(API) 정의
 * - 해석기는 구문을 구문 트리로 파싱
 * - Executor 인터페이스를 상속받아 각 노드들에 대해서 방문에 대한 메서드 구현 필요
 */
public interface Node extends Executor {
    void parse(Context context) throws ParseException;
}
