package designpattern.composite.headfirst;

import designpattern.composite.headfirst.iterator.CompositeIterator;

import java.util.Iterator;
import java.util.ArrayList;
import java.util.List;

/**
 * Composite 역할
 * - MenuComponent 객체들을 담는 컨테이너 역할
 * - 내용물 안에는 Menu 또는 MenuItem 객체들이 존재
 */
public class Menu extends MenuComponent {
    private final List<MenuComponent> components = new ArrayList<>();
    private final String name;
    private final String description;

    public Menu(String name, String description) {
        this.name = name;
        this.description = description;
    }

    @Override
    public void add(MenuComponent menuComponent) {
        components.add(menuComponent);
    }

    @Override
    public void remove(MenuComponent menuComponent) {
        components.remove(menuComponent);
    }

    @Override
    public MenuComponent getChild(int i) {
        return components.get(i);
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
    public Iterator<MenuComponent> createIterator() {
        return new CompositeIterator(components.iterator());
    }

    @Override
    public void print() {
        System.out.printf("\n\t%s, %s\n", getName(), getDescription());
        System.out.println("\t----------------------------");

        // 컴포지트를 구성하는 컴포넌트에 대한 메서드 호출
        for(MenuComponent component : components) {
            component.print();
        }

    }
}
