package designpattern.ChainOfResponsibility.main.trouble;

/**
 * 처리해야 하는 문제
 * - 클라이언트는 해당 클래스 객체를 처리해야 하는 상황
 * - handler 패키지의 구체 클래스들이 해당 문제를 처리
 */
public class Trouble {
    private final int id;

    public Trouble(int id) {
        this.id = id;
    }

    public int getId() {
        return id;
    }

    @Override
    public String toString() {
        return String.format("[Trouble %d]", id);
    }
}
