package designpattern.decorator.main.decorator;

import designpattern.decorator.main.component.Display;

public class FullBorder extends Border {

    public FullBorder(Display display) {
        super(display);
    }

    @Override
    public int getColumns() {
        // 내용물 좌우 방향에 장식
        return 1 + display.getColumns() + 1;
    }

    @Override
    public int getRows() {
        // 내용물 상하 방향에 장식
        return 1 + display.getRows() + 1;
    }

    @Override
    public String getRowText(int row) {

        if (row == 0 || row == display.getRows() + 1) {
            // 내용물의 상하단에 장식
            return String.format("%c%s%c", '+', makeLine('-', display.getColumns()), '+');
        } else {
            // 내용물 자체 장식
            return String.format("%c%s%c", '|', display.getRowText(row - 1), '|');
        }
    }

    private String makeLine(char ch, int count) {
        StringBuilder buffer = new StringBuilder();
        for (int i = 0; i < count; i++) buffer.append(ch);

        return buffer.toString();
    }
}
