package designpattern.interpreter.main.exercise.facade;

/**
 * Factory Method 패턴 적용
 * - Executor 객체를 생성하는 역할
 */
public interface ExecutorFactory {
    Executor createExecutor(String name);
}
