package designpattern.bridge.main.impl;

// Exercise 3
public class PatternDisplayImpl extends DisplayImpl {
    private final char header;
    private final char deco;
    private final char footer;

    public PatternDisplayImpl(char header, char deco, char footer) {
        this.header = header;
        this.deco = deco;
        this.footer = footer;
    }

    @Override
    public void rawOpen() {
        System.out.print(header);
    }

    @Override
    public void rawPrint() {
        System.out.print(deco);
    }

    @Override
    public void rawClose() {
        System.out.println(footer);
    }
}
