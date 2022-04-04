package designpattern.command.main.drawer;

import java.awt.*;

// 그림 그리기 대상 표현
public interface Drawable {
    void init();
    void draw(int x, int y);
    void setColor(Color color);
}
