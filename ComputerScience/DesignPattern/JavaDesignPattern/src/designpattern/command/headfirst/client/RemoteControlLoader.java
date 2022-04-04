package designpattern.command.headfirst.client;

import designpattern.command.headfirst.invoker.RemoteControl;
import designpattern.command.headfirst.receiver.*;
import designpattern.command.headfirst.command.*;

/**
 * Command 객체와 Receiver 객체를 생성하여 연결
 * - 둘을 연결한 Invoker 객체 생성
 */
public class RemoteControlLoader {
    public static RemoteControl getRemoteControl() {
        RemoteControl control = new RemoteControl(5);

        Light roomLight = new Light("Room");
        Light livingRoomLight = new Light("Living Room");
        Door entrance = new Door("Entrance");
        Door garageDoor = new Door("Garage");
        Stereo stereo = new Stereo("Living Room");

        control.setCommand(0, new LightOnCommand(roomLight), new LightOffCommand(roomLight));
        control.setCommand(1, new LightOnCommand(livingRoomLight), new LightOffCommand(livingRoomLight));
        control.setCommand(2, new DoorOpenCommand(entrance), new DoorCloseCommand(entrance));
        control.setCommand(3, new DoorOpenCommand(garageDoor), new DoorCloseCommand(garageDoor));
        control.setCommand(4, new StereoOnWithCDCommand(stereo), new StereoOnWithCDCommand(stereo));

        return control;
    }
}
