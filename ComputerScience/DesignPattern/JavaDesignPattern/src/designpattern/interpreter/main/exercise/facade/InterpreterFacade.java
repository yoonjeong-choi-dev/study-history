package designpattern.interpreter.main.exercise.facade;

import designpattern.interpreter.main.exercise.language.Context;
import designpattern.interpreter.main.exercise.language.Node;
import designpattern.interpreter.main.exercise.language.ParseException;
import designpattern.interpreter.main.exercise.language.nonterminal.ProgramNode;

/**
 * 퍼사드 패턴 적용
 */
public class InterpreterFacade implements Executor {

    private final ExecutorFactory factory;
    private Context context;
    private Node root;

    public InterpreterFacade(ExecutorFactory factory) {
        this.factory = factory;
    }

    public boolean parse(String programText) {
        boolean ok = true;
        context = new Context(programText);
        context.setExecutorFactory(factory);

        root = new ProgramNode();

        try {
            root.parse(context);
            System.out.println("Parsed Result : " + root.toString());
        } catch (ParseException e) {
            e.printStackTrace();
            ok = false;
        }
        return ok;
    }

    @Override
    public void execute() throws ExecuteException {
        try {
            root.execute();
        } catch (ExecuteException e) {
            e.printStackTrace();
        }
    }
}
