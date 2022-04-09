package designpattern.interpreter.main.exercise.gui;

import designpattern.interpreter.main.exercise.facade.InterpreterFacade;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class TurtleFrame extends Frame implements ActionListener {

    private final TurtleCanvas canvas = new TurtleCanvas(400, 400);
    private final InterpreterFacade facade = new InterpreterFacade(canvas);
    private final TextField programTextField = new TextField();

    public TurtleFrame(String title, String program) {
        super(title);
        programTextField.setText(program);

        canvas.setExecutor(facade);

        setLayout(new BorderLayout());
        programTextField.addActionListener(this);

        this.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                System.exit(0);
            }
        });

        add(programTextField, BorderLayout.NORTH);
        add(canvas, BorderLayout.CENTER);

        pack();
        parseAndExecute();
        show();
    }

    private void parseAndExecute() {
        String programText = programTextField.getText();
        System.out.printf("Program : %s\n", programText);
        facade.parse(programText);
        canvas.repaint();
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if(e.getSource() == programTextField) {
            parseAndExecute();
        }
    }
}
