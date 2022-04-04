package designpattern.command.headfirst.receiver;

public class Light {
    private final String name;

    public Light(String name) {
        this.name = name;
    }

    public void turnOn() {
        System.out.printf("%s light : ON\n", name);
    }

    public void turnOff() {
        System.out.printf("%s light : OFF\n", name);
    }
}
