package designpattern.command.headfirst.command;

import designpattern.command.headfirst.receiver.Light;

public class LightOnCommand implements Command{
    private final Light light;

    public LightOnCommand(Light light) {
        this.light = light;
    }

    @Override
    public void execute() {
        light.turnOn();
    }

    @Override
    public void undo() {
        light.turnOff();
    }
}
