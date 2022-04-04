package designpattern.command.main.drawer;

import designpattern.command.main.command.Command;

import java.awt.Point;

// 점 그리기 명령
public class DrawCommand implements Command {
    // 그리는 대상 및 점 위치
    protected Drawable drawable;
    private final Point position;

    public DrawCommand(Drawable drawable, Point position) {
        this.drawable = drawable;
        this.position = position;
    }

    @Override
    public void execute() {
        drawable.draw(position.x, position.y);
    }
}
