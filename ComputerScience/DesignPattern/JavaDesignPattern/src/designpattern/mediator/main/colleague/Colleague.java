package designpattern.mediator.main.colleague;

import designpattern.mediator.main.mediator.Mediator;

/**
 * Mediator 인터페이스가 중재하는 인터페이스
 * - Mediator 인터페이스와의 통신을 하기 위한 API 제공
 */
public interface Colleague {
    // 자신의 중재자를 설정하는 세터 메서드
    void setMediator(Mediator mediator);

    // 중재자가 상황 판단하에 해당 Colleague 객체 활성화 여부 설정 메서드
    void setColleagueEnabled(boolean enabled);
}
