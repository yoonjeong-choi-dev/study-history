package designpattern.abstractfactory.main.factory;

import java.util.ArrayList;
import java.util.List;

// 다수의 Item 추상 클래스에 대한 컬렉션
public abstract class Tray extends Item {

    // Item 추상 클래스 컬렌션
    protected List<Item> tray = new ArrayList<>();

    public Tray(String caption) {
        super(caption);
    }

    public void add(Item item) {
        tray.add(item);
    }
}
