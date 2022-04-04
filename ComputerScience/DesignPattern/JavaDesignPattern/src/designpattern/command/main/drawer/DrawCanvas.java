package designpattern.command.main.drawer;

import designpattern.command.main.command.MacroCommand;

import java.awt.*;

/**
 * Receiver 역할을 하는 클래스
 * - Command 역할이 명령을 실행할 때의 대상이 되는 클래스
 * - Command 역할의 명령을 받아들이는 역할
 * Invoker 역할을 하는 클래스
 * - Command 역할의 명령을 호출
 */
public class DrawCanvas extends Canvas implements Drawable {

    // 그림 그리기 형식
    private Color color;
    private int radius;

    private final MacroCommand history;

    public DrawCanvas(int width, int height, MacroCommand history) {
        setSize(width, height);
        setBackground(Color.white);

        this.history = history;
        init();
    }

    // 히스토리를 이용하여 다시 그리기
    @Override
    public void paint(Graphics g) {
        history.execute();
    }

    @Override
    public void init() {
        color = Color.black;
        radius = 6;
    }

    @Override
    public void draw(int x, int y) {
        Graphics graphics = getGraphics();
        graphics.setColor(color);
        graphics.fillOval(x - radius, y - radius, radius * 2, radius * 2);
    }

    @Override
    public void setColor(Color color) {
        this.color = color;
    }
}
