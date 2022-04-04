package designpattern.command.headfirst;

import designpattern.command.headfirst.client.RemoteControlLoader;
import designpattern.command.headfirst.invoker.RemoteControl;

public class Main {
    public static void main(String[] args) {
        RemoteControl control = RemoteControlLoader.getRemoteControl();

        control.clickOnButton(1);
        control.clickOffButton(0);
        control.clickOnButton(2);
        control.clickOffButton(3);

        for(int i=0;i<5;i++){
            control.undo();
        }

        control.clickOnButton(4);
    }
}
