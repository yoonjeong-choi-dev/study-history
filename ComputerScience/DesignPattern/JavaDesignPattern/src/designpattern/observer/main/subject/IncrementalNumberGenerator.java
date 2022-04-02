package designpattern.observer.main.subject;

public class IncrementalNumberGenerator extends Subject {

    private int number;
    private final int start;
    private final int end;
    private final int step;

    public IncrementalNumberGenerator(int start, int end, int step) {
        this.start = start;
        this.end = end;
        this.step = step;
    }

    @Override
    public int getData() {
        return number;
    }

    @Override
    public void execute() {
        for (int i = start; i < end; i += step) {
            number = i;
            notifyObservers();
        }
    }
}
