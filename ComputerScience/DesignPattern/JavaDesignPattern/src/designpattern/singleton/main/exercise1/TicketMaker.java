package designpattern.singleton.main.exercise1;

public class TicketMaker {
    // 싱글톤 패턴 적용
    private static final TicketMaker instance = new TicketMaker();

    private TicketMaker() {
    }

    public static TicketMaker getInstance() {
        return instance;
    }


    private int ticket = 1000;

    public synchronized int getNextTicketNumber() {
        return ticket++;
    }
}
