package designpattern.templatemethod.main;

/**
 * 메인 로직 흐름을 정의하는 추상 클래스
 *  추상 메서드들을 조합하여 메인 메서드 정의(템플릿 메서드)
 *  추상 메서드들의 구현은 하위 클래스가 담당
 */
public abstract class AbstractDisplay {
    // 하위 클래스에서 구현해야 하는 추상 메서드
    protected abstract void open();
    protected abstract void print();
    protected abstract void close();

    // 템플릿 메서드 - 메인 로직 : 추상 메서드들의 조합으로 구성
    // 템플릿 메서드는 하위 클래스에서 오버라이드가 되지 않도록 final 선언
    public final void display() {
        open();
        for(int i=0;i<5;i++){
            print();
        }
        close();
    }
}
