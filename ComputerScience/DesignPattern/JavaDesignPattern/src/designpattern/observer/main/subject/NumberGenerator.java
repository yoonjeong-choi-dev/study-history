package designpattern.observer.main.subject;

import java.util.Random;

public class NumberGenerator extends Subject {
    private final Random random = new Random();
    private int number;

    public int getData() {
        return number;
    }

    @Override
    public void execute() {
        for (int i = 0; i < 20; i++) {
            number = random.nextInt(50);
            notifyObservers();
        }
    }
}
