package designpattern.observer.main.observer;

import designpattern.observer.main.subject.Subject;

public class DigitObserver implements Observer {

    @Override
    public void update(Subject subject) {
        System.out.println("Digit Observer : " + subject.getData());
        try {
            Thread.sleep(100);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
