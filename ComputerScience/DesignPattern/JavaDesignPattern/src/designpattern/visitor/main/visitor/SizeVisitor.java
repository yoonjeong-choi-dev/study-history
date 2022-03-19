package designpattern.visitor.main.visitor;

import designpattern.visitor.main.element.Directory;
import designpattern.visitor.main.element.Entry;
import designpattern.visitor.main.element.File;

import java.util.Iterator;

// Exercise 2
public class SizeVisitor extends Visitor {

    private int size = 0;

    public int getSize() {
        return size;
    }

    @Override
    public void visit(File file) {
        size += file.getSize();
    }

    @Override
    public void visit(Directory directory) {
        // 자신의 하위 엔트리들에 대한 방문 요청
        Iterator<Entry> itr = directory.iterator();
        while (itr.hasNext()) {
            Entry entry = itr.next();

            // 디렉터리의 각 요소들에 대한 방문 요청
            entry.accept(this);
        }
    }
}
