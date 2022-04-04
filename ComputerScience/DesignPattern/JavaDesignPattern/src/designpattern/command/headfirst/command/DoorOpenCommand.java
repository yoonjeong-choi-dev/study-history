package designpattern.command.headfirst.command;

import designpattern.command.headfirst.receiver.Door;

public class DoorOpenCommand implements Command {

    private final Door door;

    public DoorOpenCommand(Door door) {
        this.door = door;
    }

    @Override
    public void execute() {
        door.open();
    }

    @Override
    public void undo() {
        door.close();
    }
}
