package designpattern.observer.headfirst.observer;

/**
 * 특정 객체를 관찰하는 관찰자(구독자)
 * - 관찰 대상자가 변경을 알릴 때(notify), 각 관찰자에게 전달되는 데이터를 위한 API
 */
public interface Observer {
    void update(float temperature, float humidity, float pressure);
}
