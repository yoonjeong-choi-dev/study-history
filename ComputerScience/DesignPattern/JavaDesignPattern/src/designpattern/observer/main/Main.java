package designpattern.observer.main;

import designpattern.observer.main.observer.DigitObserver;
import designpattern.observer.main.observer.GraphObserver;
import designpattern.observer.main.observer.Observer;
import designpattern.observer.main.subject.IncrementalNumberGenerator;
import designpattern.observer.main.subject.NumberGenerator;
import designpattern.observer.main.subject.Subject;

public class Main {
    public static void main(String[] args) {
        // 관찰 대상 1개와 관찰자 2개 생성
        Observer observer1 = new DigitObserver();
        Observer observer2 = new GraphObserver();

        Subject subject = new NumberGenerator();
        subject.addObserver(observer1);
        subject.addObserver(observer2);

        subject.execute();

        Subject subject2 = new IncrementalNumberGenerator(10, 50,5);
        subject2.addObserver(observer1);
        subject2.addObserver(observer2);
        subject2.execute();
    }
}
