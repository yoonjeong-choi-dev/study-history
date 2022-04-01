package designpattern.mediator.main.mediator;

/**
 * 중개인 인터페이스
 * - Colleague 인터페이스 간 통신을 조정하는 API 제공
 * - Colleague 인터페이스와 통신해야 하는 형태에 따라 다양한 메서드가 추가될 수 있음
 */
public interface Mediator {
    void createColleague();

    void colleagueChanged();
}
