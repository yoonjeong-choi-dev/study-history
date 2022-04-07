package designpattern.memento.main.game;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 * Memento 클래스를 사용하는 Originator
 * - 자신의 상태를 저장하여 Memento 객체 생성
 * - 이전 상태를 저장한 Memento 객체를 이용하여 상태를 이전으로 되돌리는 역할
 */
public class Gamer {

    private static final String[] fruitsName = {"Apple", "Grape", "Banana", "Orange"};

    private int money;
    private List<String> fruits = new ArrayList<>();
    private final Random random = new Random();

    public Gamer(int money) {
        this.money = money;
    }

    public int getMoney() {
        return money;
    }

    public void bet() {
        // 주사위 던지기
        int dice = random.nextInt(6) + 1;

        // 주사위 결과에 따라 상태 변경
        if (dice == 1) {
            money += 100;
            System.out.println("소지금이 100원 증가하였습니다");
        } else if (dice == 2) {
            money /= 2;
            System.out.println("소지금이 절반이 되었습니다");
        } else if (dice == 6) {
            String fruit = getFruit();
            fruits.add(fruit);
            System.out.printf("과일(%s)을 받았습니다\n", fruit);
        } else {
            System.out.println("아무런 변경이 없습니다");
        }
    }

    private String getFruit() {
        String prefix = "";
        if (random.nextBoolean()) {
            prefix = "맛있는 ";
        }

        return prefix + fruitsName[random.nextInt(fruitsName.length)];
    }

    public GamerMemento createMemento() {
        // 현재 상태를 이용하여 메멘토 인스턴스 생성
        GamerMemento memento = new GamerMemento(money);
        for (String fruit : fruits) {
            // 맛있는 음식만 저장
            if (fruit.startsWith("맛있는 ")) {
                memento.addFruit(fruit);
            }
        }
        return memento;
    }

    public void restoreMemento(GamerMemento memento) {
        // Undo 기능 : 이전 상태 복구
        this.money = memento.money;
        this.fruits = memento.getFruits();
    }

    @Override
    public String toString() {
        return String.format("Money : %d, Fruits : %s", money, fruits.toString());
    }
}
