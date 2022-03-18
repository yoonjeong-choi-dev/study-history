package designpattern.decorator.main.decorator;

import designpattern.decorator.main.component.Display;

// Exercise 1
public class UpDownBorder extends Border {

    // 장식에 사용될 문자
    private final char borderChar;


    public UpDownBorder(Display display, char borderChar) {
        super(display);
        this.borderChar = borderChar;
    }


    @Override
    public int getColumns() {

        return display.getColumns();
    }

    @Override
    public int getRows() {
        // 문자열 상하에 장식문자를 더함
        return 1 + display.getRows() + 1;
    }

    @Override
    public String getRowText(int row) {
        if (row == 0 || row == getRows() - 1) {
            return makeLine();
        } else {
            return display.getRowText(row - 1);
        }

    }

    private String makeLine() {
        StringBuilder buffer = new StringBuilder();
        for (int i = 0; i < getColumns(); i++) buffer.append(borderChar);

        return buffer.toString();
    }
}
