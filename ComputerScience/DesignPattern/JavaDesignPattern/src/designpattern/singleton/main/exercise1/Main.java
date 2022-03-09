package designpattern.singleton.main.exercise1;

public class Main {
    public static void main(String[] args) {
        TicketMaker t1 = TicketMaker.getInstance();
        TicketMaker t2 = TicketMaker.getInstance();

        System.out.println("Create ticket : " + t1.getNextTicketNumber());
        System.out.println("Create ticket : " + t2.getNextTicketNumber());
        System.out.println("Create ticket : " + t1.getNextTicketNumber());
    }
}
