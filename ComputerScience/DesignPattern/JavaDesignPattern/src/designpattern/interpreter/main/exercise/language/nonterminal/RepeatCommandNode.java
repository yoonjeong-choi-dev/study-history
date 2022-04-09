package designpattern.interpreter.main.exercise.language.nonterminal;

import designpattern.interpreter.main.exercise.facade.ExecuteException;
import designpattern.interpreter.main.exercise.language.Context;
import designpattern.interpreter.main.exercise.language.Node;
import designpattern.interpreter.main.exercise.language.ParseException;

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

    @Override
    public void execute() throws ExecuteException {
        // repeatNumber 만큼 반복
        for(int i=0;i<repeatNumber;i++){
            commandListNode.execute();
        }
    }
}
