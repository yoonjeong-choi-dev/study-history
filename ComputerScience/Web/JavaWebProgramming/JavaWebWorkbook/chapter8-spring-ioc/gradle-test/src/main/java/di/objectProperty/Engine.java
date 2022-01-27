package di.objectProperty;

public class Engine {
    String maker;
    int cc;

    public Engine() {}

    public Engine(String maker) {
        this.maker = maker;
    }

    public String getMaker() {
        return  maker;
    }

    public void setMaker(String maker) {
        this.maker = maker;
    }

    public int getCc() {
        return cc;
    }

    public void setCc(int cc) {
        this.cc = cc;
    }

    @Override
    public String toString() {
        return "Engine{" +
                "maker='" + maker + '\'' +
                ", cc=" + cc +
                '}';
    }
}
