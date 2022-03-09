package designpattern.singleton.headfirst;

/**
 * 멀티스레드 환경에서 안정적으로 인스턴스를 생성하는 방법을 제공
 * 1. getInstance() 메서드에 synchronized 키워드를 이용하여 스레드 동기화하는 방식을 사용할 수도 있음
 * - 메서드 전체가 실행될 때까지 한 스레드가 작업 점령
 * - 해당 메서드가 리소스를 많이 잡아먹는 경우 멀티스레드 환경에서 병목 지점이 될 가능성 존재
 * 2. double checking looking 방식으로 getInstance() 메서드 동기화
 * - 인스턴스가 생성되었는지 확인 후, 생성되지 않은 경우에만 스레드 동기화
 */
public class MultiThreadSingleton {
    // volatile : 멀티스레드 환경에서 CPU 캐시가 아닌 메인 메모리에서 값을 읽도록 하기 위한 키워드
    // => 멀티스레드에서 변수 값의 불일치를 없애기 위함
    private volatile static MultiThreadSingleton instance;

    private MultiThreadSingleton() {
    }

    public static MultiThreadSingleton getInstance() {
        if (instance == null) {
            // 인스턴스 생성이 안된 경우에만 스레드 동기화
            synchronized (MultiThreadSingleton.class) {
                if (instance == null) {
                    instance = new MultiThreadSingleton();
                }
            }
        }

        return instance;
    }
}
