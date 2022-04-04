package designpattern.state.main.states;

import designpattern.state.main.context.Context;

/**
 * 특정 상태에 대한 API를 제공하는 인터페이스
 * - 제공하는 API 메서드들은 사건에 대응해서 호출되는 기능들을 규정
 * - 구현체는 특정 상태에 대응하는 메서드들을 구현
 * - 각 메서드들은 상태를 관리하는 Context 객체를 인자로 받음
 */
public interface State {
    void setClock(Context context, int hour);
    void useSafe(Context context);
    void ringAlarm(Context context);
    void callPhone(Context context);
}
