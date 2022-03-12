package designpattern.strategy.main.strategies;

import designpattern.strategy.main.Hand;

import java.util.Random;

// Exercise 1
public class RandomStrategy implements Strategy {

    private final Random random;

    public RandomStrategy(int seed) {
        random = new Random(seed);
    }

    @Override
    public Hand nextHand() {
        // 무작위로 내는 전략
        return Hand.getHand(random.nextInt(3));
    }

    @Override
    public void study(boolean isWin) {
        // 학습할 것이 없음
    }
}
