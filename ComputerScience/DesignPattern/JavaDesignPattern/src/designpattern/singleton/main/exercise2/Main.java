package designpattern.singleton.main.exercise2;

public class Main {
    public static void main(String[] args) {
        for (int i = 0; i < 12; i++) {
            System.out.println(i + " : " + Triple.getInstance(i % 3));
        }
    }
}
