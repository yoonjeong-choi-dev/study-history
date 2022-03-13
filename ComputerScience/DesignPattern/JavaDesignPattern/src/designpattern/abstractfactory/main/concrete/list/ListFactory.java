package designpattern.abstractfactory.main.concrete.list;

import designpattern.abstractfactory.main.factory.Factory;
import designpattern.abstractfactory.main.factory.Link;
import designpattern.abstractfactory.main.factory.Page;
import designpattern.abstractfactory.main.factory.Tray;

public class ListFactory extends Factory {
    @Override
    public Link createLink(String caption, String url) {
        return new ListLink(caption, url);
    }

    @Override
    public Tray createTray(String caption) {
        return new ListTray(caption);
    }

    @Override
    public Page createPage(String title, String author) {
        return new ListPage(title, author);
    }
}
