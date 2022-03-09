package designpattern.singleton.main.exercise2;

public class Triple {
    // 싱글톤 패턴 확장 -> 인스턴수 개수를 다수로 제한
    private static final Triple[] instances = {new Triple(0), new Triple(1), new Triple(2)};

    private final int id;

    private Triple(int id) {
        this.id = id;
    }

    public static Triple getInstance(int id) {
        return instances[id];
    }

    @Override
    public String toString() {
        return "Triple { " + "id=" + id + " }";
    }
}
