package designpattern.command.headfirst.invoker;

import designpattern.command.headfirst.command.Command;
import designpattern.command.headfirst.command.NoCommand;

import java.util.Stack;

/**
 * Invoker 역할
 * - Command 인터페이스 구현체의 메서드를 호출하는 역할
 */
public class RemoteControl {
    private final int numSlots;
    private final Command[] onCommands;
    private final Command[] offCommands;
    private final Stack<Command> history = new Stack<>();

    public RemoteControl(int numSlots) {
        this.numSlots = numSlots;
        onCommands = new Command[numSlots];
        offCommands = new Command[numSlots];

        Command noCommand = NoCommand.getInstance();
        for (int i = 0; i < numSlots; i++) {
            onCommands[i] = noCommand;
            offCommands[i] = noCommand;
        }
    }

    public void setCommand(int slot, Command onCommand, Command offCommand) {
        checkSlotAvailable(slot);
        onCommands[slot] = onCommand;
        offCommands[slot] = offCommand;
    }

    public void clickOnButton(int slot) {
        checkSlotAvailable(slot);
        onCommands[slot].execute();

        history.push(onCommands[slot]);
    }

    public void clickOffButton(int slot) {
        checkSlotAvailable(slot);
        offCommands[slot].execute();

        history.push(offCommands[slot]);
    }

    public void undo() {
        if(!history.isEmpty()) {
            Command command = history.pop();
            command.undo();
        } else {
            System.out.println("There is no command to undo");
        }
    }

    private void checkSlotAvailable(int slot) {
        if (slot < 0 || slot >= numSlots) {
            throw new IndexOutOfBoundsException();
        }
    }
}
