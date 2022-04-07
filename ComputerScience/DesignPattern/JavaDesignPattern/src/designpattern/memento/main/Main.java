package designpattern.memento.main;

import designpattern.memento.main.game.Gamer;
import designpattern.memento.main.game.GamerMemento;

/**
 * Caretaker 클래스
 * - Originator 객체를 이용하는 클래스
 * - Originator 객체의 히스토리를 관리하기 위해 Memento 객체를 가지고 있음
 * - '어느 시점'에서 스냅샷을 찍고, 복구할지를 결정하는 역할
 * - 실제 스냡샷을 찍고 복구하는 것은 Gamer 클래스의 역할
 */
public class Main {
    public static void main(String[] args) {
        Gamer gamer = new Gamer(100);
        GamerMemento memento = gamer.createMemento();

        for(int i=0;i<100;i++){
            System.out.println("=============================");
            System.out.printf("[%d-th State] %s\n", i, gamer);

            // 게임 진행
            gamer.bet();

            System.out.printf("Current Money : %d\n", gamer.getMoney());

            if(gamer.getMoney() > memento.getMoney()) {
                // 이전보다 소지금이 증가한 경우에는 메멘토에 저장
                System.out.println("Save the gamer state to the memento");
                memento = gamer.createMemento();
            } else if(gamer.getMoney() < memento.getMoney() /2) {
                // 이전보다 소지금이 절반 이상 감소한 경우 복구
                System.out.println("Restore the gamer state from the memento");
                gamer.restoreMemento(memento);
            }

            System.out.println("=============================");
        }
    }
}
