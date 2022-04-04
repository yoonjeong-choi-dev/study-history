package designpattern.state.main.states;

import designpattern.state.main.context.Context;

public class NightState implements State {

    // 상태는 하나의 객체만 필요하므로 싱글턴 패턴 적용
    private static final NightState instance = new NightState();

    private NightState() {
    }

    public static State getInstance() {
        return instance;
    }

    @Override
    public void setClock(Context context, int hour) {
        // 주간 시간으로 변경 시, 컨텍스트의 상태 변경 메서드 호출
        if (hour >= 9 && hour < 17) {
            context.changeState(DayState.getInstance());
        }
    }

    @Override
    public void useSafe(Context context) {
        context.callSecurityCenter("[Night] WARN : USE THE SAFE!!!");
    }

    @Override
    public void ringAlarm(Context context) {
        context.callSecurityCenter("[Night]Ring the emergency alarm!");
    }

    @Override
    public void callPhone(Context context) {
        context.callSecurityCenter("[Night]Night phone call");
    }

    @Override
    public String toString() {
        return "[Night]";
    }
}
