package designpattern.interpreter.main.exercise.language.terminal;

import designpattern.interpreter.main.exercise.facade.ExecuteException;
import designpattern.interpreter.main.exercise.facade.Executor;
import designpattern.interpreter.main.exercise.language.Context;
import designpattern.interpreter.main.exercise.language.Node;
import designpattern.interpreter.main.exercise.language.ParseException;

/**
 * 구문 트리의 말단 노드
 * - <primitive command> : : = go | right | left
 * - BNF의 Terminal Expression 대응
 * - 더 이상 커맨드가 전개되지 않는 문법 규칙의 종착점
 */
public class PrimitiveCommandNode implements Node {

    private String name;
    private Executor executor;

    @Override
    public void parse(Context context) throws ParseException {
        name = context.currentToken();
        context.skipToken(name);
        executor = context.createExecutor(name);

        if (!name.equals("go") && !name.equals("right") && !name.equals("left")) {

        }
    }

    @Override
    public String toString() {
        return name;
    }

    @Override
    public void execute() throws ExecuteException {
        if (executor == null) {
            throw new ExecuteException(String.format("%s command is not defined", name));
        } else {
            executor.execute();
        }
    }
}
