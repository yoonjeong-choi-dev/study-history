package designpattern.mediator.main.mediator;

import designpattern.mediator.main.colleague.ColleagueButton;
import designpattern.mediator.main.colleague.ColleagueCheckbox;
import designpattern.mediator.main.colleague.ColleagueTextField;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

// UI 컴포넌트들을 중재하는 중개자 구체 클래스
public class LoginFrame extends Frame implements ActionListener, Mediator {

    // UI 컴포넌트들
    private ColleagueCheckbox checkGuest;
    private ColleagueCheckbox checkLogin;
    private ColleagueTextField textUser;
    private ColleagueTextField textPassword;
    private ColleagueButton buttonOk;
    private ColleagueButton buttonCancel;

    public LoginFrame(String title) {
        super(title);

        // 레이아웃 설정
        setBackground(Color.lightGray);
        setLayout(new GridLayout(4, 2));

        // UI 컴포넌트 생성
        createColleague();

        // UI 컴포넌트 배치
        add(checkGuest);
        add(checkLogin);

        add(new Label("Username :"));
        add(textUser);

        add(new Label("Password :"));
        add(textPassword);

        add(buttonOk);
        add(buttonCancel);

        // UI 컴포넌트 활성화 설정
        colleagueChanged();

        // 표시
        pack();
        show();
    }

    @Override
    public void createColleague() {
        // UI 컴포넌트 생성
        CheckboxGroup group = new CheckboxGroup();
        checkGuest = new ColleagueCheckbox("Guest", group, true);
        checkLogin = new ColleagueCheckbox("Login", group, false);

        textUser = new ColleagueTextField("", 10);
        textPassword = new ColleagueTextField("", 10);
        textPassword.setEchoChar('*');

        buttonOk = new ColleagueButton("OK");
        buttonCancel = new ColleagueButton("Cancel");

        // 중재자 설정
        checkGuest.setMediator(this);
        checkLogin.setMediator(this);
        textUser.setMediator(this);
        textPassword.setMediator(this);
        buttonOk.setMediator(this);
        buttonCancel.setMediator(this);

        // 리스너 등록
        checkGuest.addItemListener(checkGuest);
        checkLogin.addItemListener(checkLogin);
        textUser.addTextListener(textUser);
        textPassword.addTextListener(textPassword);
        buttonOk.addActionListener(this);
        buttonCancel.addActionListener(this);

    }

    @Override
    public void colleagueChanged() {
        // 현재 로그인 폼의 상태에 따라 UI 컴포넌트 활성화 여부 처리
        // 독립적인 컴포넌트들 사이의 중재 역할을 하는 메인 로직
        if(checkGuest.getState()) {
            textUser.setColleagueEnabled(false);
            textPassword.setColleagueEnabled(false);
            buttonOk.setColleagueEnabled(true);
        } else {
            textUser.setColleagueEnabled(true);
            checkComponentState();
        }
    }

    // text 필드 변경에 대한 UI 컴포넌트 활성화 여부 변경
    private void checkComponentState() {
        if (textUser.getText().length() > 0) {
            textPassword.setColleagueEnabled(true);

            buttonOk.setColleagueEnabled(textPassword.getText().length() > 0);
        } else {
            textPassword.setColleagueEnabled(false);
            buttonOk.setEnabled(false);
        }
    }

    @Override
    public void actionPerformed(ActionEvent actionEvent) {
        System.out.println(actionEvent.toString());
        System.exit(0);
    }
}
