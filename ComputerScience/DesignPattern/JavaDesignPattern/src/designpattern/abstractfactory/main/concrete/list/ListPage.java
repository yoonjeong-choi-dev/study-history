package designpattern.abstractfactory.main.concrete.list;

import designpattern.abstractfactory.main.factory.Item;
import designpattern.abstractfactory.main.factory.Page;

import java.util.Iterator;

public class ListPage extends Page {

    public ListPage(String title, String author) {
        super(title, author);
    }

    @Override
    public String makeHTML() {
        // 각 컨텐츠들(Item)을 이용하여 HTML 생성
        StringBuilder buffer = new StringBuilder();
        buffer.append(String.format("<html><head><meta charset=\"UTF-8\"><title>%s</title></head>", title));
        buffer.append(String.format("<h1>%s</h1>", title));

        buffer.append("<ul>\n");
        // 이터레이터 패턴 적용
        Iterator<Item> iterator = content.iterator();
        while (iterator.hasNext()) {
            Item item = iterator.next();
            buffer.append(item.makeHTML());
        }
        buffer.append("</ul>\n</li>");

        buffer.append(String.format("<hr><address>%s</address>", author));
        buffer.append("</body></html>");
        return buffer.toString();
    }
}
