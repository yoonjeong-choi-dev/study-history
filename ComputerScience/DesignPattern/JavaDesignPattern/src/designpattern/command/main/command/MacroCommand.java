package designpattern.command.main.command;

import java.util.Stack;

// 명령들에 대한 히스토리 표현
public class MacroCommand implements Command {

    // 명령의 집합 : undo 기능을 위해 stack 자료구조 사용
    private final Stack<Command> commands = new Stack<>();

    @Override
    public void execute() {
        // 스택에 있는 명령들 실행
        for (Command command : commands) {
            command.execute();
        }
    }

    public void append(Command command) {
        // 자기 자신이 아닌 명령을 스택에 추가(무한 루프 방지)
        if (command != this) {
            commands.push(command);
        }
    }

    public void undo() {
        // 스택의 top 명령어 삭제
        if (!commands.isEmpty()) {
            commands.pop();
        }
    }

    public void clear() {
        commands.clear();
    }
}
