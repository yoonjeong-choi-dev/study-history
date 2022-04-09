package designpattern.interpreter.main.language.nonterminal;

import designpattern.interpreter.main.language.Context;
import designpattern.interpreter.main.language.Node;
import designpattern.interpreter.main.language.ParseException;

/**
 * <repeat command> : : = repeat <number> <command list>
 */
public class RepeatCommandNode implements Node {

    private int repeatNumber;
    private Node commandListNode;

    @Override
    public void parse(Context context) throws ParseException {
        context.skipToken("repeat");
        repeatNumber = context.currentNumber();
        context.nextToken();

        commandListNode = new CommandListNode();
        commandListNode.parse(context);
    }

    @Override
    public String toString() {
        return String.format("[repeat %d %s ]", repeatNumber, commandListNode);
    }
}
