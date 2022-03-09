package designpattern.adapter.headfirst.Target;

public class WildTurkey implements Turkey {
    @Override
    public void gobble() {
        System.out.println("Gobble Gobble~");
    }

    @Override
    public void fly() {
        System.out.println("Fly over the ground with short distance~");
    }
}
