package designpattern.memento.main.game;

import java.util.ArrayList;
import java.util.List;

/**
 * Gamer 객체에 대한 Memento 클래스
 * - 동일 패키지의 Gamer 객체에서만 자유로운 접근을 위해 접근 제어자를 (default)로 설정
 * - 즉 상태 변경을 저장하는 것은 동일 패키지 내의 메멘토가 저장하는 대상만 가능
 * - Gamer 객체의 상태를 저장하는 클래스
 */
public class GamerMemento {
    int money;
    List<String> fruits;

    GamerMemento(int money) {
        this.money = money;
        this.fruits = new ArrayList<>();
    }

    public int getMoney() {
        return money;
    }

    void addFruit(String fruit) {
        fruits.add(fruit);
    }

    List<String> getFruits() {
        return new ArrayList<>(fruits);
    }
}
