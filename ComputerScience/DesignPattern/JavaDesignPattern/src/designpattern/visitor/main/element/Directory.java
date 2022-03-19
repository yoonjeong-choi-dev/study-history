package designpattern.visitor.main.element;

import designpattern.visitor.main.visitor.Visitor;

import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

// 폴더에 해당
// Entry 리스트를 가지고 있음
public class Directory extends Entry {
    private final String name;
    private final List<Entry> entries;

    public Directory(String name) {
        this.name = name;
        this.entries = new ArrayList<>();
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public int getSize() {
        // 재귀적인 구조를 가지므로, 폴더를 구성하는 엔트리들(파일/폴더)의 크기를 합하여 반환
        int size = 0;
        for (Entry entry : entries) {
            size += entry.getSize();
        }
        return size;
    }

    @Override
    public Entry add(Entry entry) {
        entries.add(entry);
        return this;
    }

    @Override
    public Iterator<Entry> iterator() {
        return entries.iterator();
    }

    @Override
    public void accept(Visitor visitor) {
        // 자기 자신을 방문하라고 방문자에게 요청
        visitor.visit(this);
    }
}
