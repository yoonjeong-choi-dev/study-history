package designpattern.visitor.main.visitor;

import designpattern.visitor.main.element.Directory;
import designpattern.visitor.main.element.Entry;
import designpattern.visitor.main.element.File;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

// Exercise 1
public class FileFindVisitor extends Visitor {
    private final String target;
    private final List<Entry> founds = new ArrayList<>();

    public FileFindVisitor(String target) {
        if (!target.startsWith("."))
            this.target = "." + target;
        else
            this.target = target;
    }

    public List<Entry> getFoundFiles() {
        return founds;
    }

    @Override
    public void visit(File file) {
        // 해당 파일 확장자 검사
        if (file.getName().endsWith(target)) {
            founds.add(file);
        }
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
