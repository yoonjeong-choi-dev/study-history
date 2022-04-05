package designpattern.flyweight.main;

import designpattern.flyweight.main.client.BigString;
import designpattern.flyweight.main.factory.BigCharFactory;

public class Main {
    public static void main(String[] args) {
        String testString = "2022-03-19";
        BigString bs = new BigString(testString);
        bs.print();

        exercise2();
    }


    private static void exercise2() {
        String test = "123456789123456789123456789123456789123456789";
        sharedExample(test);
        unSharedExample(test);
    }

    private static void sharedExample(String test) {
        Runtime.getRuntime().gc();

        BigCharFactory factory = BigCharFactory.getInstance();
        for (int i = 0; i < test.length(); i++) {
            factory.getBigChar(test.charAt(i));
        }

        long used = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
        System.out.printf("Shared Used Memory : %d\n", used);
    }

    private static void unSharedExample(String test) {
        Runtime.getRuntime().gc();

        BigCharFactory factory = BigCharFactory.getInstance();
        for (int i = 0; i < test.length(); i++) {
            factory.getBigChar(test.charAt(i), false);
        }

        long used = Runtime.getRuntime().totalMemory() - Runtime.getRuntime().freeMemory();
        System.out.printf("Unshared Used Memory : %d\n", used);
    }
}
