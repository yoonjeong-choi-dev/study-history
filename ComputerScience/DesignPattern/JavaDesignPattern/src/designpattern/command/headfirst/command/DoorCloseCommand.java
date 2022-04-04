package designpattern.command.headfirst.command;

import designpattern.command.headfirst.receiver.Door;

public class DoorCloseCommand implements Command {

    private final Door door;

    public DoorCloseCommand(Door door) {
        this.door = door;
    }

    @Override
    public void execute() {
        door.close();
    }

    @Override
    public void undo() {
        door.open();
    }
}
