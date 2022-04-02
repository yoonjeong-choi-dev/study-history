package designpattern.observer.main.subject;

import designpattern.observer.main.observer.Observer;

import java.util.ArrayList;
import java.util.List;

/**
 * 관찰되는 대상에 해당하는 추상 클래스
 * - 자신을 관찰하는 관찰자들 객체를 가지고 있음
 * - 자신의 상태 변경 시, 등록된 관찰자 객체에게 통보
 */
public abstract class Subject {
    private final List<Observer> observers = new ArrayList<>();

    public void addObserver(Observer observer) {
        observers.add(observer);
    }

    public void deleteObserver(Observer observer) {
        observers.remove(observer);
    }

    public void notifyObservers() {
        for(Observer observer : observers) {
           observer.update(this);
        }
    }

    public abstract int getData();
    public abstract void execute();
}
