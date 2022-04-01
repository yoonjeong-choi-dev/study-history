package designpattern.mediator.main.colleague;

import designpattern.mediator.main.mediator.Mediator;

import java.awt.TextField;
import java.awt.event.TextEvent;
import java.awt.event.TextListener;

public class ColleagueTextField extends TextField implements TextListener, Colleague {

    private Mediator mediator;

    public ColleagueTextField(String text, int columns) {
        super(text, columns);
    }

    @Override
    public void setMediator(Mediator mediator) {
        this.mediator = mediator;
    }

    @Override
    public void setColleagueEnabled(boolean enabled) {
        setEnabled(enabled);
    }

    @Override
    public void textValueChanged(TextEvent textEvent) {
        // 텍스트 변경 시, 중재인에게 알림
        mediator.colleagueChanged();
    }
}
