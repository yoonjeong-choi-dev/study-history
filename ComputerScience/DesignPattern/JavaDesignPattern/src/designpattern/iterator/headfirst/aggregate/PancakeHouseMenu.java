package designpattern.iterator.headfirst.aggregate;

import designpattern.iterator.headfirst.MenuItem;
import designpattern.iterator.headfirst.iterator.PancakeHouseIterator;
import designpattern.iterator.headfirst.iterator.Iterator;

import java.util.ArrayList;

// MenuItem 요소들로 구성된 메뉴 컬렉션 컨테이너
public class PancakeHouseMenu implements Menu {
    // 리스트를 이용하여 구현
    ArrayList<MenuItem> menuItems;

    public PancakeHouseMenu() {
        menuItems = new ArrayList<>();

        addItem("PancakeHouseMenu1", "with PancakeHouse", true, 2.99);
        addItem("PancakeHouseMenu2", "with PancakeHouse", false, 2.99);
        addItem("PancakeHouseMenu3", "with PancakeHouse", true, 3.99);
        addItem("PancakeHouseMenu4", "with PancakeHouse", true, 4.99);
    }

    public void addItem(String name, String description, boolean vegetarian, double price) {
        MenuItem menuItem = new MenuItem(name, description, vegetarian, price);
        menuItems.add(menuItem);
    }

    public ArrayList<MenuItem> getMenuItems() {
        return menuItems;
    }

    @Override
    public Iterator createIterator() {
        return new PancakeHouseIterator(menuItems);
    }
}
