package designpattern.interpreter.main.language.nonterminal;

import designpattern.interpreter.main.language.Context;
import designpattern.interpreter.main.language.Node;
import designpattern.interpreter.main.language.ParseException;
import designpattern.interpreter.main.language.terminal.PrimitiveCommandNode;

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
}
