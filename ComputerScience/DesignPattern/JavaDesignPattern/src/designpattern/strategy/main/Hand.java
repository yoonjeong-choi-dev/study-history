package designpattern.strategy.main;


import java.util.HashMap;

public class Hand {
    public static final int ROCK = 0;
    public static final int SCISSOR = 1;
    public static final int PAPER = 2;

    // 가위바위보의 손을 표시
    public static final Hand[] hand = {
            new Hand(ROCK),
            new Hand(SCISSOR),
            new Hand(PAPER),
    };

    // 가위바위보 문자열 표현
    private static final String[] name = {
            "주먹", "가위", "보",
    };

    // 싱글톤 패턴 응용 => 정적 메서드를 통해서만 인스턴스 생성
    public static Hand getHand(int handIndex) {
        return new Hand(handIndex);
    }

    private final int value;

    private Hand(int value) {
        this.value = value;
    }

    public boolean isStrongerThan(Hand hand) {
        return fight(hand) == 1;
    }

    public boolean isWeakerThan(Hand hand) {
        return fight(hand) == -1;
    }

    private int fight(Hand hand) {
        if (value == hand.value) {
            return 0;
        } else if ((this.value + 1) % 3 == hand.value) {
            return 1;
        } else {
            return -1;
        }
    }

    @Override
    public String toString() {
        return name[value];
    }
}
