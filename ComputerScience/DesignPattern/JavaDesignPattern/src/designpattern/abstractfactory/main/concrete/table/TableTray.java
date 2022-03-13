package designpattern.abstractfactory.main.concrete.table;

import designpattern.abstractfactory.main.factory.Item;
import designpattern.abstractfactory.main.factory.Tray;

import java.util.Iterator;

public class TableTray extends Tray {

    public TableTray(String caption) {
        super(caption);
    }

    @Override
    public String makeHTML() {
        StringBuilder buffer = new StringBuilder();
        buffer.append("<td>");
        buffer.append("<table width=\"100%\" border=\"1\"><tr>");
        buffer.append(String.format("<td bgcolor=\"#cccccc\" align=\"center\" colspan=\"%d\">", tray.size()));
        buffer.append("<b>").append(caption).append("\n").append("</b></td>\n").append("</tr>\n");

        // 이터레이터 패턴 적용
        buffer.append("<tr>\n");
        Iterator<Item> iterator = tray.iterator();
        while (iterator.hasNext()) {
            Item item = iterator.next();
            buffer.append(item.makeHTML());
        }
        buffer.append("</tr>\n</table>");

        return buffer.toString();
    }
}
