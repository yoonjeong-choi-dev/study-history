package designpattern.singleton.main;

public class Singleton {
    // 하나의 인스턴스를 저장하는 정적 필드
    private static final Singleton instance = new Singleton();

    public static Singleton getInstance() {
        return instance;
    }

    private Singleton() {
        System.out.println("The instance is created");
    }
}
