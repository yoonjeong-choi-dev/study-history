package designpattern.command.main.drawer;

import designpattern.command.main.command.Command;

import java.awt.*;

public class ColorCommand implements Command {
    // 그리는 대상 및 색상
    protected Drawable drawable;
    protected Color color;

    public ColorCommand(Drawable drawable, Color color) {
        this.drawable = drawable;
        this.color = color;
    }

    @Override
    public void execute() {
        drawable.setColor(color);
    }
}
