package designpattern.visitor.main.element;

import designpattern.visitor.main.visitor.Visitor;

public class File extends Entry {

    private final String name;
    private final int size;

    public File(String name, int size) {
        this.name = name;
        this.size = size;
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public int getSize() {
        return size;
    }

    @Override
    public void accept(Visitor visitor) {
        // 자기 자신을 방문하라고 방문자에게 요청
        visitor.visit(this);
    }
}
