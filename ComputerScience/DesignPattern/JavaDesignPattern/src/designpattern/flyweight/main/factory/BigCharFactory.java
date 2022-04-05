package designpattern.flyweight.main.factory;

import designpattern.flyweight.main.flyweight.BigChar;

import java.util.HashMap;

/**
 * Flyweight 인스턴스를 생성하는 팩토리 역할
 * - 풀을 가지고 있어, 이미 생성된 인스턴스의 경우 기존 인스턴스를 이용하는 방식
 * - 풀을 이용하기 때문에 하나의 인스턴스만 존재해야 하므로 싱글턴 적용
 * - 멀티스레드 환경에서, 인스턴스 생성 메서드 getBigChar 내부 생성 여부 확인 로직이 두 번 이상 발생하여 인스턴스를 2번 이상 생성하는 문제를 방지하기 위해 synchronized 키워드 이용
 */
public class BigCharFactory {
    // 플라이웨이트 인스턴스 풀
    private final HashMap<Character, BigChar> pool = new HashMap<>();

    // 싱글톤 적용
    private static final BigCharFactory instance = new BigCharFactory();

    private BigCharFactory() {
    }

    public static BigCharFactory getInstance() {
        return instance;
    }

    public synchronized BigChar getBigChar(char charName) {
        BigChar bc = pool.get(charName);
        if (bc == null) {
            // 아직 생성된적이 없으면 새로 생성하여 풀에 등록
            bc = new BigChar(charName);
            pool.put(charName, bc);
        }

        return bc;
    }

    public synchronized BigChar getBigChar(char charName, boolean shared) {
        if (shared) {
            return getBigChar(charName);
        } else {
            return new BigChar(charName);
        }
    }
}
