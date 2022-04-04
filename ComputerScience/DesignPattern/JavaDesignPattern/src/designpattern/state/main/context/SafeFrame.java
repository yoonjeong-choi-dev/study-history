package designpattern.state.main.context;

import designpattern.decorator.main.decorator.Border;
import designpattern.state.main.states.DayState;
import designpattern.state.main.states.State;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SafeFrame extends Frame implements ActionListener, Context {

    private final TextField textClock = new TextField(60);
    private final TextArea textScreen = new TextArea(10, 60);
    private final Button buttonUse = new Button("Use Safe");
    private final Button buttonAlarm = new Button("Emergency Alarm");
    private final Button buttonPhone = new Button("Phone Call");
    private final Button buttonExit = new Button("Exit");

    private State state = DayState.getInstance();

    public SafeFrame(String title) {
        super(title);
        setBackground(Color.lightGray);
        setLayout(new BorderLayout());

        // Clock
        add(textClock, BorderLayout.NORTH);
        textClock.setEditable(false);

        // Screen
        add(textScreen, BorderLayout.CENTER);
        textScreen.setEditable(false);

        // Button Panel
        Panel buttonPanel = new Panel();
        buttonPanel.add(buttonUse);
        buttonPanel.add(buttonAlarm);
        buttonPanel.add(buttonPhone);
        buttonPanel.add(buttonExit);
        add(buttonPanel, BorderLayout.SOUTH);

        pack();
        show();

        // Add Event Listener
        buttonUse.addActionListener(this);
        buttonAlarm.addActionListener(this);
        buttonPhone.addActionListener(this);
        buttonExit.addActionListener(this);
    }

    @Override
    public void setClock(int hour) {
        String clockString = "현재 시간은 ";
        if (hour < 10) {
            clockString += String.format("0%d:00", hour);
        } else {
            clockString += String.format("%d:00", hour);
        }

        System.out.println(clockString);
        textClock.setText(clockString);

        state.setClock(this, hour);
    }

    @Override
    public void changeState(State state) {
        System.out.printf("Current state is changed from %s to %s\n", this.state, state);
        this.state = state;
    }

    @Override
    public void callSecurityCenter(String message) {
        textScreen.append("CALL!! " + message + "\n");
    }

    @Override
    public void recordLog(String message) {
        textScreen.append("RECORD.. " + message + "\n");
    }

    @Override
    public void actionPerformed(ActionEvent actionEvent) {
        // 각 버튼에 대한 이벤트 리스너 설정
        // => State 패턴을 이용하여 현재 시간 상태에 대한 조건없이 상태 객체를 이용하여 프로세스 진행
        Object button = actionEvent.getSource();
        if (button == buttonUse) {
            state.useSafe(this);
        } else if (button == buttonAlarm) {
            state.ringAlarm(this);
        } else if (button == buttonPhone) {
            state.callPhone(this);
        } else if (button == buttonExit) {
            System.exit(0);
        } else {
            System.out.println("Something wrong...");
        }
    }
}
