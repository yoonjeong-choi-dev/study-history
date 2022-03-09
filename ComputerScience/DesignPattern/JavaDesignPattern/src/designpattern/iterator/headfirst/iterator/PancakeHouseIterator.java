package designpattern.iterator.headfirst.iterator;

import java.util.List;

import designpattern.iterator.headfirst.MenuItem;
import designpattern.iterator.headfirst.iterator.Iterator;

public class PancakeHouseIterator implements Iterator {
    List<MenuItem> items;
    int position = 0;

    public PancakeHouseIterator(List<MenuItem> items) {
        this.items = items;
    }

    @Override
    public boolean hasNext() {
        return position < items.size() && items.get(position) != null;
    }

    @Override
    public Object next() {
        MenuItem item = items.get(position);
        position++;
        return item;
    }
}
