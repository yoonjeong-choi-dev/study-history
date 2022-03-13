package designpattern.abstractfactory.main.concrete.table;

import designpattern.abstractfactory.main.factory.Item;
import designpattern.abstractfactory.main.factory.Page;

import java.util.Iterator;

public class TablePage extends Page {

    public TablePage(String title, String author) {
        super(title, author);
    }

    @Override
    public String makeHTML() {
        // 각 컨텐츠들(Item)을 이용하여 HTML 생성
        StringBuilder buffer = new StringBuilder();
        buffer.append(String.format("<html><head><meta charset=\"UTF-8\"><title>%s</title></head>", title));
        buffer.append(String.format("<h1>%s</h1>", title));

        buffer.append("<table width=\"80%\" border=\"3\">\n");
        // 이터레이터 패턴 적용
        Iterator<Item> iterator = content.iterator();
        while (iterator.hasNext()) {
            Item item = iterator.next();
            buffer.append("<tr>").append(item.makeHTML()).append("</tr>");
        }
        buffer.append("</table>");

        buffer.append(String.format("<hr><address>%s</address>", author));
        buffer.append("</body></html>");
        return buffer.toString();
    }
}
