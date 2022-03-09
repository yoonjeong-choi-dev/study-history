package designpattern.singleton.headfirst;

// 고전적인 방식의 싱글턴 패턴
public class ClassicSingleton {
    // 유일한 인스턴스를 저장하기 위한 정적 변수
    private static ClassicSingleton instance;

    // 생성자의 접근 제어자를 private으로 설정함으로써 외부에서 생성 불가
    private ClassicSingleton() {
    }

    public static ClassicSingleton getInstance() {
        // Lazy Initialization
        // 멀티스테르 환경에서 인스턴스 생성 조건을 체크하고 객체 생성 과정 순서가 꼬이면 유일한 객체를 보장 X
        if (instance == null) {
            instance = new ClassicSingleton();
        }

        return instance;
    }
}
