package designpattern.iterator.headfirst;

import designpattern.iterator.headfirst.iterator.Iterator;
import designpattern.iterator.headfirst.aggregate.Menu;

// 서로 다른 컨테이너를 구현한 클래스들을 이용하는 클라이언트 객체
// 아래 코드에는 구체화된 클래스 정보가 없음
public class Waitress {
    Menu pancakeHouseMenu;
    Menu dinerMenu;

    public Waitress(Menu pancakeHouseMenu, Menu dinerMenu) {
        this.pancakeHouseMenu = pancakeHouseMenu;
        this.dinerMenu = dinerMenu;
    }

    public void printMenu() {
        System.out.println("=================================");
        System.out.println("All Menu");
        printIterator(pancakeHouseMenu.createIterator());
        printIterator(dinerMenu.createIterator());
        System.out.println("=================================");
    }

    public void printBreakfastMenu() {
        System.out.println("=================================");
        System.out.println("Breakfast Menu");
        printIterator(pancakeHouseMenu.createIterator());
        System.out.println("=================================");
    }

    public void printLunchMenu() {
        System.out.println("=================================");
        System.out.println("Lunch Menu");
        printIterator(dinerMenu.createIterator());
        System.out.println("=================================");
    }

    public void printVegetarianMenu() {
        System.out.println("=================================");
        System.out.println("Vegetarian Menu");
        printIteratorVegetarianOnly(pancakeHouseMenu.createIterator());
        printIteratorVegetarianOnly(dinerMenu.createIterator());
        System.out.println("=================================");
    }

    private void printIterator(Iterator itr) {
        while(itr.hasNext()) {
            System.out.println(itr.next());
        }
    }

    private void printIteratorVegetarianOnly(Iterator iterator) {
        while(iterator.hasNext()) {
            MenuItem item = (MenuItem) iterator.next();
            if(item.isVegetarian()) System.out.println(item);
        }
    }
}
