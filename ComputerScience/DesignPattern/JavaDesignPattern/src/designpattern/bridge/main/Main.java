package designpattern.bridge.main;

import designpattern.bridge.main.func.CountDisplay;
import designpattern.bridge.main.func.Display;
import designpattern.bridge.main.func.IncreaseDisplay;
import designpattern.bridge.main.func.RandomCountDisplay;
import designpattern.bridge.main.impl.FileDisplayImpl;
import designpattern.bridge.main.impl.PatternDisplayImpl;
import designpattern.bridge.main.impl.StringDisplayImpl;

public class Main {
    public static void main(String[] args) {
        // 클래스 계층에 있는 다양한 객체 생성
        Display d1 = new Display(new StringDisplayImpl("Hello, YJ"));
        CountDisplay d2 = new CountDisplay(new StringDisplayImpl("Hello, Counter"));

        d1.display();
        d2.display();
        d2.multiDisplay(5);

        // 연습문제
        System.out.println("Exercise 1");
        RandomCountDisplay rd = new RandomCountDisplay(new StringDisplayImpl("Exercise 1 Test"));
        rd.randomDisplay(10);

        System.out.println("Exercise 2");
        Display fd = new Display(new FileDisplayImpl("README.md"));
        fd.display();

        System.out.println("Exercise 3-1");
        IncreaseDisplay id1 = new IncreaseDisplay(new PatternDisplayImpl('<', '*', '>'));
        id1.increaseDisplay(4);

        System.out.println("Exercise 3-1");
        IncreaseDisplay id2 = new IncreaseDisplay(new PatternDisplayImpl('|', '#', '-'));
        id2.increaseDisplay(6);
    }
}
