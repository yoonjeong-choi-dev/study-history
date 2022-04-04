package designpattern.command.headfirst.command;

import designpattern.command.headfirst.receiver.Stereo;

public class StereoOffCommand implements Command {

    Stereo stereo;

    public StereoOffCommand(Stereo stereo) {
        this.stereo = stereo;
    }

    @Override
    public void execute() {
        stereo.turnOff();
    }

    @Override
    public void undo() {
        stereo.setCD();
        stereo.setVolume(10);
        stereo.turnOn();
    }
}
