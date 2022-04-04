package designpattern.command.headfirst.command;

// 커맨드 널체크를 피하기 위해 만든 깡통 클래스
// 싱글턴 패턴 적용
public class NoCommand implements Command {

    private static final NoCommand instance = new NoCommand();

    private NoCommand() {
    }

    public static NoCommand getInstance() {
        return instance;
    }

    @Override
    public void execute() {
    }

    @Override
    public void undo() {
    }
}
