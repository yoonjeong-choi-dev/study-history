package designpattern.observer.headfirst.display;

import designpattern.observer.headfirst.observer.Observer;

public class CurrentConditionDisplay implements Observer, Display {

    private final String name;
    private float temperature;
    private float humidity;

    public CurrentConditionDisplay(String name) {
        this.name = name;
    }

    @Override
    public void display() {
        System.out.printf("[Display %s] Current Condition : %.2f F degree and %.2f %% humidity\n", name, temperature, humidity);
    }

    @Override
    public void update(float temperature, float humidity, float pressure) {
        this.temperature = temperature;
        this.humidity = humidity;
        display();
    }
}
