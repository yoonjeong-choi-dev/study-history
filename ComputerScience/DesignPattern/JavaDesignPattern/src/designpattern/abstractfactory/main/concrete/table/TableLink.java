package designpattern.abstractfactory.main.concrete.table;

import designpattern.abstractfactory.main.factory.Link;

public class TableLink extends Link {
    public TableLink(String caption, String url) {
        super(caption, url);
    }

    @Override
    public String makeHTML() {
        return String.format("\t<td><a href='%s'>%s</a></td>\n", url, caption);
    }
}
