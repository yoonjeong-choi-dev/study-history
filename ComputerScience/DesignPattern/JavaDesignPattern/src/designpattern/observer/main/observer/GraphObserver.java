package designpattern.observer.main.observer;

import designpattern.observer.main.subject.Subject;

public class GraphObserver implements Observer {
    @Override
    public void update(Subject subject) {
        System.out.print("Graph Observer : ");

        int count = subject.getData();
        for (int i = 0; i < count; i++) {
            System.out.print("*");
        }
        System.out.println();

        try {
            Thread.sleep(100);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
