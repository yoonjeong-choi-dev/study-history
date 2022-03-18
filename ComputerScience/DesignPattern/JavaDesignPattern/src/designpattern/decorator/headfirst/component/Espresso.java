package designpattern.decorator.headfirst.component;

public class Espresso implements Beverage {
    private final String description;

    public Espresso() {
        this.description = "Simple Espresso";
    }

    @Override
    public String getDescription() {
        return description;
    }

    @Override
    public double cost() {
        return 0.75;
    }
}
