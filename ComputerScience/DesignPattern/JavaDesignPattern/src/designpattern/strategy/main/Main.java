package designpattern.strategy.main;


import designpattern.strategy.main.strategies.ProbStrategy;
import designpattern.strategy.main.strategies.RandomStrategy;
import designpattern.strategy.main.strategies.SimpleStrategy;

public class Main {
    public static void main(String[] args) {
        // 테스트용 시드
        int seed1 = 713, seed2 = 1993, seed3 = 2022;
        int numTest = 10000;

        Player player1 = new Player("YJ", new SimpleStrategy(seed1));
        Player player2 = new Player("Smart YJ", new ProbStrategy(seed2));
        Player player3 = new Player("Random", new RandomStrategy(seed3));

        System.out.println("===============================");
        System.out.println("Example 1");
        System.out.println("===============================");
        simulate(player1, player2, numTest);


        System.out.println("===============================");
        System.out.println("Exercise 1");
        System.out.println("===============================");
        simulate(player3, player2, numTest);
    }

    private static void simulate(Player player1, Player player2, int numTest) {

        for (int i = 0; i < numTest; i++) {
            Hand hand1 = player1.nextHand();
            Hand hand2 = player2.nextHand();

            if (hand1.isStrongerThan(hand2)) {
                player1.win();
                player2.lose();
            } else if (hand2.isStrongerThan(hand1)) {
                player1.lose();
                player2.win();
            } else {
                player1.draw();
                player2.draw();
            }

            if (i % 1000 == 0) {
                System.out.printf("At %d\n", i);
                System.out.println(player1);
                System.out.println(player2);
            }
        }


        System.out.println("Result : ");
        System.out.println(player1);
        System.out.println(player2);
    }
}
