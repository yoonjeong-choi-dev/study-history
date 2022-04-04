package designpattern.command.headfirst.receiver;

public class Stereo {
    private final String name;
    private int volume;


    public Stereo(String name) {
        this.name = name;
    }

    public void turnOn() {
        System.out.printf("%s Stereo : ON with volume %d\n", name, volume);
    }

    public void turnOff() {
        System.out.printf("%s Stereo : OFF\n", name);
    }

    public void setCD() {
        System.out.printf("%s Stereo : CD is loaded\n", name);
    }

    public void setVolume(int volume) {
        this.volume = volume;
        System.out.printf("%s Stereo : volume is set with %d\n", name, volume);
    }
}
