package designpattern.ChainOfResponsibility.main.handler;

import designpattern.ChainOfResponsibility.main.trouble.Trouble;

/**
 * 요구 사항을 처리하는 API를 제공하는 추상 클래스
 * - 여기서 처리해야 하는 요구 사항은 Trouble 객체에 해당
 * - resolve 메서드를 통해 자신이 처리 가능하면 처리한 후 true 반환
 * - support 메서드는 템플릿 메서드로, resolve 메서드를 호출하여 자신이 처리 못하는 경우 다음 Support 클래스로 책임을 떠넘긴다
 */
public abstract class Support {
    private final String name;
    private Support next;

    public Support(String name) {
        this.name = name;
    }

    public Support setNext(Support next) {
        // 체인 생성을 위해서 다음 담당 객체를 반환
        this.next = next;
        return next;
    }

    // 템플릿 메서드 패턴 적용
    public final void support(Trouble trouble) {
        if (resolve(trouble)) {
            done(trouble);
        } else if (next != null) {
            // 떠넘길 대상이 있는 경우, 대상에게 책임 전가
            next.support(trouble);
        } else {
            fail(trouble);
        }
    }

    protected abstract boolean resolve(Trouble trouble);

    protected void done(Trouble trouble) {
        System.out.printf("%s is resolved by %s\n", trouble, this);
    }

    protected void fail(Trouble trouble) {
        // 떠넘길 대상이 없는 상태에서 처리를 못한 상황
        // 여기서는 표준 출력으로 표현하지만, 예외를 던지는 경우도 있음
        System.out.printf("%s cannot be resolved\n", trouble);
    }


    @Override
    public String toString() {
        return String.format("[Support %s]", name);
    }
}
