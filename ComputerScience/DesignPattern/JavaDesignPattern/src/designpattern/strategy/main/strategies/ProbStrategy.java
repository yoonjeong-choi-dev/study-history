package designpattern.strategy.main.strategies;

import designpattern.strategy.main.Hand;

import java.util.Random;

public class ProbStrategy implements Strategy {
    private final Random random;
    private int prevValue = 0;
    private int curValue = 0;
    private final int[][] history = {
            {1, 1, 1,},
            {1, 1, 1,},
            {1, 1, 1,},
    };

    public ProbStrategy(int seed) {
        random = new Random(seed);
    }

    @Override
    public Hand nextHand() {
        // 직전에 prev 손을 내었을 때, 다음에 내야하는 손을 가중치를 주어 랜덤 계산
        int weight = random.nextInt(getSum(prevValue));

        int next;
        if (weight < history[prevValue][0]) {
            next = 0;
        } else if (weight < history[prevValue][0] + history[prevValue][1]) {
            next = 1;
        } else {
            next = 2;
        }

        prevValue = curValue;
        curValue = next;

        return Hand.getHand(curValue);
    }


    private int getSum(int prev) {
        // 직전에 prev 손을 낸 경우, 모든 승리 개수 계산
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += history[prev][i];
        }
        return sum;
    }

    @Override
    public void study(boolean isWin) {
        if (isWin) {
            history[prevValue][curValue]++;
        } else {
            history[prevValue][(curValue + 1) % 3]++;
            history[prevValue][(curValue + 2) % 3]++;
        }
    }
}
