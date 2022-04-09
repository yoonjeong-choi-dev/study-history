package designpattern.interpreter.main.language.nonterminal;

import designpattern.interpreter.main.language.Context;
import designpattern.interpreter.main.language.Node;
import designpattern.interpreter.main.language.ParseException;

import java.util.ArrayList;

/**
 * <command list> : : = <command>* end
 */
public class CommandListNode implements Node {
    private final ArrayList<Node> commandList = new ArrayList<>();

    @Override
    public void parse(Context context) throws ParseException {
        // end 커맨드가 올 때까지 파싱
        while (true) {
            if (context.currentToken() == null) {
                throw new ParseException("Missing 'end'");
            } else if (context.currentToken().equals("end")) {
                // end 커맨드가 오면 커맨드 리스트 파싱 완료
                context.skipToken("end");
                break;
            } else {
                // 각 커맨드들을 리스트에 저장
                Node commandNode = new CommandNode();
                commandNode.parse(context);
                commandList.add(commandNode);
            }
        }
    }

    @Override
    public String toString() {
        return commandList.toString();
    }
}
