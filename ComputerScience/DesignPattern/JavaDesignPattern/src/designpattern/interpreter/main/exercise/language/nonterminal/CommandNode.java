package designpattern.interpreter.main.exercise.language.nonterminal;

import designpattern.interpreter.main.exercise.facade.ExecuteException;
import designpattern.interpreter.main.exercise.language.Context;
import designpattern.interpreter.main.exercise.language.Node;
import designpattern.interpreter.main.exercise.language.ParseException;
import designpattern.interpreter.main.exercise.language.terminal.PrimitiveCommandNode;

/**
 * <command> : : = <repeat command> | <primitive command>
 */
public class CommandNode implements Node {

    private Node node;

    @Override
    public void parse(Context context) throws ParseException {
        // 커맨드가 repeat/primitive 에 따라 인스턴스 생성
        if (context.currentToken().equals("repeat")) {
            node = new RepeatCommandNode();
        } else {
            node = new PrimitiveCommandNode();
        }
        node.parse(context);
    }

    @Override
    public String toString() {
        return node.toString();
    }

    @Override
    public void execute() throws ExecuteException {
        node.execute();
    }
}
