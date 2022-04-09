package designpattern.interpreter.main.exercise.facade;

/**
 * Visitor 패턴 적용
 * - 파싱된 구문 트리를 구성하는 노드들을 방문하면서 처리하는 메서드 제공
 */
public interface Executor {
    void execute() throws ExecuteException;
}
