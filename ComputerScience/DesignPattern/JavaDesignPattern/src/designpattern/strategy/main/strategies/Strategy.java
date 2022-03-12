package designpattern.strategy.main.strategies;

import designpattern.strategy.main.Hand;

public interface Strategy {
    // 전략을 이용하여 다음에 낼 손 결정
    Hand nextHand();

    // 전력을 학습하기 위한 메서드
    void study(boolean isWin);
}
