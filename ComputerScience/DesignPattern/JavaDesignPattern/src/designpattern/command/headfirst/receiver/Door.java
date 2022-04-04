package designpattern.command.headfirst.receiver;

public class Door {
    private final String name;

    public Door(String name) {
        this.name = name;
    }

    public void open() {
        System.out.printf("%s Door : OPEN\n", name);
    }

    public void close() {
        System.out.printf("%s Door : CLOSED\n", name);
    }
}
