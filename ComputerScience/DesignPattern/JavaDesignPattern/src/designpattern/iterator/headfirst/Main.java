package designpattern.iterator.headfirst;

import designpattern.iterator.headfirst.aggregate.DinerMenu;
import designpattern.iterator.headfirst.aggregate.Menu;
import designpattern.iterator.headfirst.aggregate.PancakeHouseMenu;

public class Main {
    public static void main(String[] args) {
        // Aggregate 객체 생성
        Menu pancakeHouseMenu = new PancakeHouseMenu();
        Menu dinerMenu = new DinerMenu();

        // 웨이터 객체 생성 : 클라이언트 객체
        Waitress waitress = new Waitress(pancakeHouseMenu, dinerMenu);
        waitress.printMenu();
        waitress.printVegetarianMenu();
    }
}
