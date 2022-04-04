package designpattern.state.main.context;

import designpattern.state.main.states.State;

/**
 * 상태를 관리하는 역할을 하는 인터페이스
 * - 현재 상태에 대해서 사용자가 호출하는 API 규정
 * - 사용자는 현재 상태가 추상화된 상태에서 사건에 대응하는 메서드들을 호출하여 사용
 */
public interface Context {
    void setClock(int hour);
    void changeState(State state);
    void callSecurityCenter(String message);
    void recordLog(String message);
}
