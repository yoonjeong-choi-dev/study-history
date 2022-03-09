package designpattern.iterator.headfirst.aggregate;

import designpattern.iterator.headfirst.iterator.DinerIterator;
import designpattern.iterator.headfirst.MenuItem;
import designpattern.iterator.headfirst.iterator.Iterator;

// MenuItem 요소들로 구성된 메뉴 컬렉션 컨테이너
public class DinerMenu implements Menu {
    // 배열을 이용하여 구현
    static final int MAX_ITEMS = 6;
    int curIndex = 0;
    MenuItem[] menuItems;

    public DinerMenu() {
        menuItems = new MenuItem[MAX_ITEMS];

        addItem("DinerMenu1", "with Diner", true, 1.99);
        addItem("DinerMenu2", "with Diner", false, 0.99);
        addItem("DinerMenu3", "with Diner", true, 1.59);
        addItem("DinerMenu4", "with Diner", false, 14.99);
    }

    public void addItem(String name, String description, boolean vegetarian, double price) {
        if (curIndex >= MAX_ITEMS) {
            System.out.println("Sorry.. Menu Items are full. Cannot add new menu!");
            return;
        }

        MenuItem menuItem = new MenuItem(name, description, vegetarian, price);
        menuItems[curIndex++] = menuItem;
    }

    @Override
    public Iterator createIterator() {
        return new DinerIterator(menuItems);
    }
}
