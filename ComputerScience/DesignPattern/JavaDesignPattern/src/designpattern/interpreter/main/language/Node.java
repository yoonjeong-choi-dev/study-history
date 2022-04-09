package designpattern.interpreter.main.language;

/**
 * Abstract Expression 역할
 * - 파싱된 구문 트리를 구성하는 노드의 공통 인터페이스(API) 정의
 * - 해석기는 구문을 구문 트리로 파싱
 */
public interface Node {
    void parse(Context context) throws ParseException;
}
