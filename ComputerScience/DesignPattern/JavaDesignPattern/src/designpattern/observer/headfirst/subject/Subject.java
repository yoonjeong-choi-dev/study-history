package designpattern.observer.headfirst.subject;

import designpattern.observer.headfirst.observer.Observer;

/**
 * 구독자가 구독하는 주제
 * - 구독자(관찰자)가 관찰하는 객체의 인터페이스 i.e 관찰이 되는 대상
 * - 구독 등록 및 해제 API 제공
 * - 구독자들에게 알림을 하는 API 제공
 */
public interface Subject {
    void registerObserver(Observer observer);

    void removeObserver(Observer observer);

    void notifyObserver();
}
