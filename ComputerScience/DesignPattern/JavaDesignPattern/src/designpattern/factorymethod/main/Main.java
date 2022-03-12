package designpattern.factorymethod.main;

import designpattern.factorymethod.main.framework.Factory;
import designpattern.factorymethod.main.framework.Product;
import designpattern.factorymethod.main.idcard.IDCardFactory;

public class Main {
    public static void main(String[] args) {
        Factory factory = new IDCardFactory();
        Product p1 = factory.create("YJ");
        Product p2 = factory.create("최윤정");
        Product p3 = factory.create("Yoon jeong");

        p1.use();
        p2.use();
        p3.use();
    }
}
