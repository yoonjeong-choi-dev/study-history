package designpattern.interpreter.main.language.nonterminal;

import designpattern.interpreter.main.language.Context;
import designpattern.interpreter.main.language.Node;
import designpattern.interpreter.main.language.ParseException;

/**
 * 프로그램 시작을 나타내는 노드
 * - <program> : : = program <command list>
 * - 구문 트리의 루트 노드에 해당
 */
public class ProgramNode implements Node {
    private Node commandListNode;

    @Override
    public void parse(Context context) throws ParseException {
        context.skipToken("program");
        commandListNode = new CommandListNode();
        commandListNode.parse(context);
    }

    @Override
    public String toString() {
        return String.format("[program %s ]", commandListNode.toString());
    }
}
