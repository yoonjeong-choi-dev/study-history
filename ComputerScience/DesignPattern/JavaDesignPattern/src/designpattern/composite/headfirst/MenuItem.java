package designpattern.composite.headfirst;

import designpattern.composite.headfirst.iterator.NullIterator;

import java.util.Iterator;

/**
 * Leaf 역할
 * - Composite 패턴에서 등장하는 트리의 말단 노드
 * - 컨테이너가 아닌 실제 내용물을 표현
 */
public class MenuItem extends MenuComponent {
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

    @Override
    public String getName() {
        return name;
    }

    @Override
    public String getDescription() {
        return description;
    }

    @Override
    public boolean isVegetarian() {
        return vegetarian;
    }

    @Override
    public Iterator<MenuComponent> createIterator() {
        return new NullIterator();
    }

    @Override
    public double getPrice() {
        return price;
    }

    @Override
    public void print() {
        System.out.printf("\t%s", getName());
        if (isVegetarian()) {
            System.out.print("(v)");
        }
        System.out.printf(", %.2f\n", getPrice());
        System.out.printf("\t\t-- %s\n", getDescription());
    }
}
