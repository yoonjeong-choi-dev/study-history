package designpattern.strategy.main;

import designpattern.strategy.main.strategies.Strategy;

// 전략을 사용하는 클래스
// 전략에 해당하는 알고리즘은 특정 전략 객체에게 위임
public class Player {
    private final String name;
    private final Strategy strategy;

    private int numWin, numLose, gameCount;

    public Player(String name, Strategy strategy) {
        this.name = name;
        this.strategy = strategy;
    }

    public Hand nextHand() {
        return strategy.nextHand();
    }

    public void win() {
        strategy.study(true);
        numWin++;
        gameCount++;
    }

    public void lose() {
        strategy.study(false);
        numLose++;
        gameCount++;
    }

    public void draw() {
        gameCount++;
    }

    @Override
    public String toString() {
        return String.format("[%10s] Total: %2d, Win: %2d, Lose: %2d", name, gameCount, numWin, numLose);
    }
}
