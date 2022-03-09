package designpattern.iterator.headfirst.iterator;

import designpattern.iterator.headfirst.MenuItem;
import designpattern.iterator.headfirst.iterator.Iterator;

public class DinerIterator implements Iterator {
    MenuItem[] items;
    int position = 0;

    public DinerIterator(MenuItem[] items) {
        this.items = items;
    }

    @Override
    public boolean hasNext() {
        return position < items.length && items[position] != null;
    }

    @Override
    public Object next() {
        MenuItem item = items[position];
        position++;
        return item;
    }
}
