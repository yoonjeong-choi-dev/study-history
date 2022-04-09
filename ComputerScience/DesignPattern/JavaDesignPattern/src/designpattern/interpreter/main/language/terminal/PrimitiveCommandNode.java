package designpattern.interpreter.main.language.terminal;

import designpattern.interpreter.main.language.Context;
import designpattern.interpreter.main.language.Node;
import designpattern.interpreter.main.language.ParseException;

/**
 * 구문 트리의 말단 노드
 * - <primitive command> : : = go | right | left
 * - BNF의 Terminal Expression 대응
 * - 더 이상 커맨드가 전개되지 않는 문법 규칙의 종착점
 */
public class PrimitiveCommandNode implements Node {

    private String name;

    @Override
    public void parse(Context context) throws ParseException {
        name = context.currentToken();
        context.skipToken(name);

        if (!name.equals("go") && !name.equals("right") && !name.equals("left")) {
            throw new ParseException(String.format("%s command is not defined", name));
        }
    }

    @Override
    public String toString() {
        return name;
    }
}
