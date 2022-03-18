package designpattern.decorator.main.decorator;

import designpattern.decorator.main.component.Display;

public class SideBorder extends Border {

    // 장식에 사용될 문자
    private final char borderChar;

    public SideBorder(Display display, char borderChar) {
        super(display);
        this.borderChar = borderChar;
    }


    @Override
    public int getColumns() {
        // 문자열 양쪽에 장식문자를 더함
        return 1 + display.getColumns() + 1;
    }

    @Override
    public int getRows() {
        return display.getRows();
    }

    @Override
    public String getRowText(int row) {
        return String.format("%c%s%c", borderChar, display.getRowText(row), borderChar);
    }
}
