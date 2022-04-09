package designpattern.interpreter.main.exercise.gui;

import designpattern.interpreter.main.exercise.facade.ExecuteException;
import designpattern.interpreter.main.exercise.facade.Executor;
import designpattern.interpreter.main.exercise.facade.ExecutorFactory;

import java.awt.*;

/**
 * 팩토리 메서드의 구현체로 Executor 생성
 */
public class TurtleCanvas extends Canvas implements ExecutorFactory {
    final static int UNIT_LENGTH = 30;
    final static int DIRECTION_UP = 0;
    final static int DIRECTION_RIGHT = 3;
    final static int DIRECTION_DOWN = 6;
    final static int DIRECTION_LEFT = 9;
    final static int RELATIVE_DIRECTION_RIGHT = 3;
    final static int RELATIVE_DIRECTION_LEFT = -3;
    final static int RADIUS = 3;

    private int direction = 0;
    private Point position;
    private Executor executor;

    public TurtleCanvas(int width, int height) {
        setSize(width, height);
        initialize();
    }

    public void initialize() {
        Dimension size = getSize();
        position = new Point(size.width / 2, size.height / 2);
        direction = 0;
        setForeground(Color.red);
        setBackground(Color.white);
        Graphics g = getGraphics();
        if (g != null) {
            g.clearRect(0, 0, size.width, size.height);
        }
    }
    public void paint(Graphics g) {
        initialize();
        if (executor != null) {
            try {
                executor.execute();
            } catch (ExecuteException e) {
            }
        }
    }

    public void setExecutor(Executor executor) {
        this.executor = executor;
    }
    void setRelativeDirection(int relativeDirection) {
        setDirection(direction + relativeDirection);
    }
    void setDirection(int direction) {
        if (direction < 0) {
            direction = 12 - (-direction) % 12;
        } else {
            direction = direction % 12;
        }
        this.direction = direction % 12;
    }
    void go(int length) {
        int nextX = position.x;
        int nextY = position.y;
        switch (direction) {
            case DIRECTION_UP:
                nextY -= length;
                break;
            case DIRECTION_RIGHT:
                nextX += length;
                break;
            case DIRECTION_DOWN:
                nextY += length;
                break;
            case DIRECTION_LEFT:
                nextX -= length;
                break;
            default:
                break;
        }
        Graphics g = getGraphics();
        if (g != null) {
            g.drawLine(position.x, position.y, nextX, nextY);
            g.fillOval(nextX - RADIUS, nextY - RADIUS, RADIUS * 2 + 1, RADIUS * 2 + 1);
        }
        position.x = nextX;
        position.y = nextY;
    }

    @Override
    public Executor createExecutor(String name) {
        switch (name) {
            case "go":
                return new GoExecutor(this);
            case "right":
                return new DirectionExecutor(this, RELATIVE_DIRECTION_RIGHT);
            case "left":
                return new DirectionExecutor(this, RELATIVE_DIRECTION_LEFT);
            default:
                return null;
        }
    }
}

/**
 * Executor 구현체들
 * - 기본 명령어들에 대한 실행 클래스
 */
abstract class TurtleExecutor implements Executor {
    protected TurtleCanvas canvas;

    public TurtleExecutor(TurtleCanvas canvas) {
        this.canvas = canvas;
    }

    public abstract void execute();
}

class GoExecutor extends TurtleExecutor {
    public GoExecutor(TurtleCanvas canvas) {
        super(canvas);
    }
    public void execute() {
        canvas.go(TurtleCanvas.UNIT_LENGTH);
    }
}

class DirectionExecutor extends TurtleExecutor {
    private final int relativeDirection;
    public DirectionExecutor(TurtleCanvas canvas, int relativeDirection) {
        super(canvas);
        this.relativeDirection = relativeDirection;
    }
    public void execute() {
        canvas.setRelativeDirection(relativeDirection);
    }
}