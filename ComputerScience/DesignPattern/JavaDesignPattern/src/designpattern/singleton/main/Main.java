package designpattern.singleton.main;

public class Main {
    public static void main(String[] args) {
        Singleton o1 = Singleton.getInstance();
        Singleton o2 = Singleton.getInstance();

        if(o1 == o2) {
            System.out.println("Two instances are the same");
        } else {
            System.out.println("Two instances are different");
        }
    }
}
