package designpattern.command.headfirst.command;

import designpattern.command.headfirst.receiver.Stereo;

public class StereoOnWithCDCommand implements Command {

    Stereo stereo;

    public StereoOnWithCDCommand(Stereo stereo) {
        this.stereo = stereo;
    }

    @Override
    public void execute() {
        stereo.setCD();
        stereo.setVolume(10);
        stereo.turnOn();

    }

    @Override
    public void undo() {
        stereo.turnOff();
    }
}
