package designpattern.decorator.main.component;

import java.util.ArrayList;
import java.util.List;

public class MultiStringDisplay extends Display {

    private final List<String> list = new ArrayList<>();
    private int columnSize = 0;

    public void add(String string) {
        // 현재 추가하는 문자열의 길이 가장 긴 경우 => 다른 문자열 변환 필요
        int curSize = string.getBytes().length;
        if (columnSize < curSize) {
            columnSize = curSize;
            updateStrings();
        }

        list.add(string);
    }

    private void updateStrings() {
        for(int i=0;i<list.size();i++){
            String string = list.get(i);
            StringBuilder buffer = new StringBuilder(string);
            while (buffer.length() != columnSize) {
                buffer.append(' ');
            }
            list.set(i, buffer.toString());
        }
    }

    @Override
    public int getColumns() {
        return columnSize;
    }

    @Override
    public int getRows() {
        return list.size();
    }

    @Override
    public String getRowText(int row) {
        if (row >= 0 && row < list.size()) {
            return list.get(row);
        } else {
            return null;
        }
    }
}
