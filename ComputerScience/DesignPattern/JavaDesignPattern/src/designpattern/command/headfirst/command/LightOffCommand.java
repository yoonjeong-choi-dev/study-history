package designpattern.command.headfirst.command;

import designpattern.command.headfirst.receiver.Light;

public class LightOffCommand implements Command{
    private final Light light;

    public LightOffCommand(Light light) {
        this.light = light;
    }

    @Override
    public void execute() {
        light.turnOff();
    }

    @Override
    public void undo() {
        light.turnOn();
    }
}
