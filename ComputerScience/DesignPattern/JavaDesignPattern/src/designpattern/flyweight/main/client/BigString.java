package designpattern.flyweight.main.client;

import designpattern.flyweight.main.factory.BigCharFactory;
import designpattern.flyweight.main.flyweight.BigChar;

/**
 * Client 역할
 * - Flyweight Factory 인스턴스를 이용하여 Flyweight 인스턴스들을 생성하고 사용
 */
public class BigString {
    private BigChar[] bigChars;

    public BigString(String string) {
        bigChars = new BigChar[string.length()];
        BigCharFactory factory = BigCharFactory.getInstance();
        for (int i = 0; i < bigChars.length; i++) {
            bigChars[i] = factory.getBigChar(string.charAt(i));
        }
    }

    public void print() {
        for (BigChar bc : bigChars) {
            bc.print();
        }
    }
}
