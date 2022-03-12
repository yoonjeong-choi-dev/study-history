package designpattern.strategy.main.strategies;

import designpattern.strategy.main.Hand;

import java.util.Random;

public class SimpleStrategy implements Strategy {
    private final Random random;
    private boolean won = false;
    private Hand prevHand;

    public SimpleStrategy(int seed) {
        random = new Random(seed);
    }

    @Override
    public Hand nextHand() {
        // 직전에 이긴 경우 해당 손을 내고, 진 경우에는 랜덤
        if (!won) {
            prevHand = Hand.getHand(random.nextInt(3));
        }

        return prevHand;
    }

    @Override
    public void study(boolean isWin) {
        won = isWin;
    }
}
