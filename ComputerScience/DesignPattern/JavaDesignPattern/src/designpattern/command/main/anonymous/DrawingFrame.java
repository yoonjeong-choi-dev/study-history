package designpattern.command.main.anonymous;

import designpattern.command.main.command.Command;
import designpattern.command.main.command.MacroCommand;
import designpattern.command.main.drawer.ColorCommand;
import designpattern.command.main.drawer.DrawCanvas;
import designpattern.command.main.drawer.DrawCommand;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.HashMap;

/**
 * Client 역할
 * - Command 생성 및  Receiver 역할에게 command 객체 전달
 * - MouseMotion 및 Window 이벤트 리스너는 awt 라이브러리에서 제공하는 어댑터 클래스를 익명 클래스로 사용하여 등록
 */
public class DrawingFrame extends JFrame implements ActionListener {

    private final MacroCommand history = new MacroCommand();
    private final DrawCanvas canvas = new DrawCanvas(400, 400, history);

    private final HashMap<JButton, Color> colorButtons = new HashMap<>();
    private final JButton undoButton = new JButton("undo");
    private final JButton clearButton = new JButton("Clear");


    public DrawingFrame(String title) {
        super(title);

        this.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent windowEvent) {
                System.out.println("Exit Drawing Canvas");
                System.exit(0);
            }
        });
        canvas.addMouseMotionListener(new MouseMotionAdapter() {
            @Override
            public void mouseDragged(MouseEvent mouseEvent) {
                Command command = new DrawCommand(canvas, mouseEvent.getPoint());
                history.append(command);
                command.execute();
            }
        });

        // Init color button
        colorButtons.put(new JButton("RED"), Color.RED);
        colorButtons.put(new JButton("Green"), Color.GREEN);
        colorButtons.put(new JButton("Blue"), Color.BLUE);
        colorButtons.put(new JButton("Black"), Color.BLACK);

        Box colorBox = new Box(BoxLayout.X_AXIS);
        for (JButton button : colorButtons.keySet()) {
            colorBox.add(button);
            button.addActionListener(this);
        }


        Box buttonBox = new Box(BoxLayout.X_AXIS);
        buttonBox.add(undoButton);
        buttonBox.add(clearButton);
        undoButton.addActionListener(this);
        clearButton.addActionListener(this);

        Box mainBox = new Box(BoxLayout.Y_AXIS);
        mainBox.add(colorBox);
        mainBox.add(buttonBox);
        mainBox.add(canvas);
        this.getContentPane().add(mainBox);

        pack();
        show();
    }

    @Override
    public void actionPerformed(ActionEvent actionEvent) {
        Object target = actionEvent.getSource();

        if (target == clearButton) {
            System.out.println("Clear the canvas");
            history.clear();
            canvas.init();
            canvas.repaint();
        } else if (target == undoButton) {
            history.undo();
            canvas.repaint();
        } else {
            for (JButton button : colorButtons.keySet()) {
                if (target == button) {
                    Command command = new ColorCommand(canvas, colorButtons.get(button));
                    history.append(command);
                    command.execute();
                    break;
                }
            }
        }
    }
}
