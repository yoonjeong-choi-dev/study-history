package designpattern.iterator.headfirst;

// 반복할 요소에 해당하는 객체
public class MenuItem {
    private final String name;
    private final String description;
    private final boolean vegetarian;
    private final double price;

    public MenuItem(String name, String description, boolean vegetarian, double price) {
        this.name = name;
        this.description = description;
        this.vegetarian = vegetarian;
        this.price = price;
    }

    public String getName() {
        return name;
    }

    public String getDescription() {
        return description;
    }

    public boolean isVegetarian() {
        return vegetarian;
    }

    public double getPrice() {
        return price;
    }

    @Override
    public String toString() {
        return String.format("[Menu] %s : %s for %s. price=%f$", name, description, vegetarian ? "vegetarian" : "everyone", price);
    }
}
