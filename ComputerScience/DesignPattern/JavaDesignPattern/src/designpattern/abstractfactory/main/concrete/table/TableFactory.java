package designpattern.abstractfactory.main.concrete.table;

import designpattern.abstractfactory.main.factory.Factory;
import designpattern.abstractfactory.main.factory.Link;
import designpattern.abstractfactory.main.factory.Page;
import designpattern.abstractfactory.main.factory.Tray;

public class TableFactory extends Factory {
    @Override
    public Link createLink(String caption, String url) {
        return new TableLink(caption, url);
    }

    @Override
    public Tray createTray(String caption) {
        return new TableTray(caption);
    }

    @Override
    public Page createPage(String title, String author) {
        return new TablePage(title, author);
    }
}
