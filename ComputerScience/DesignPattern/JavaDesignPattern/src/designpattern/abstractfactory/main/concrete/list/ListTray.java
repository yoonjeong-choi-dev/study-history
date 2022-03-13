package designpattern.abstractfactory.main.concrete.list;

import designpattern.abstractfactory.main.factory.Item;
import designpattern.abstractfactory.main.factory.Tray;

import java.util.Iterator;

public class ListTray extends Tray {

    public ListTray(String caption) {
        super(caption);
    }

    @Override
    public String makeHTML() {
        StringBuilder buffer = new StringBuilder();
        buffer.append("<li>").append(caption).append("\n").append("<ul>\n");

        // 이터레이터 패턴 적용
        Iterator<Item> iterator = tray.iterator();
        while (iterator.hasNext()) {
            Item item = iterator.next();
            buffer.append(item.makeHTML());
        }
        buffer.append("</ul>\n</li>");

        return buffer.toString();
    }
}
