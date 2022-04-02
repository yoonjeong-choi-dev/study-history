package designpattern.observer.main.observer;

import designpattern.observer.main.subject.Subject;

/**
 * Subject 역할로부터 상태 변경을 통보 받는 인터페이스
 * - 관찰자 역할
 * - 관찰 대상이 이벤트를 발생 시, 관찰자의 update 메서드 호출
 */
public interface Observer {
    void update(Subject subject);
}
