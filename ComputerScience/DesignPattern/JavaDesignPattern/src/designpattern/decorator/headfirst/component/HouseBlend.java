package designpattern.decorator.headfirst.component;

public class HouseBlend implements Beverage {

    private final String description;

    public HouseBlend() {
        this.description = "House Blend Coffee";
    }

    @Override
    public String getDescription() {
        return description;
    }

    @Override
    public double cost() {
        return 1.89;
    }
}
