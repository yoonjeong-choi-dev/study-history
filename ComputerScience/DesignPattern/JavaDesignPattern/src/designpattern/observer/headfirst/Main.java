package designpattern.observer.headfirst;

import designpattern.observer.headfirst.display.CurrentConditionDisplay;
import designpattern.observer.headfirst.display.HeatIndexDisplay;
import designpattern.observer.headfirst.observer.Observer;
import designpattern.observer.headfirst.subject.WeatherData;

public class Main {
    public static void main(String[] args) {
        WeatherData weatherData = new WeatherData();

        Observer observer1 = new CurrentConditionDisplay("Conditions");
        Observer observer2 = new HeatIndexDisplay("Heat Index");

        weatherData.registerObserver(observer1);
        weatherData.registerObserver(observer2);

        System.out.println("Change the data of the subject");
        weatherData.setMeasurement(80, 65, 30.4f);

        weatherData.removeObserver(observer1);

        System.out.println("\nChange the data of the subject");
        weatherData.setMeasurement(80, 40, 21.4f);
    }
}
