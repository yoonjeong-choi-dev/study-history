package designpattern.abstractfactory.main.factory;

// Link 및 Tray 클래스를 하나로 묶기 위한 상위 클래스
// 팩토리가 생성한 제품인 Page 추상 클래스를 만들기 위한 부품
public abstract class Item {
    protected final String caption;

    public Item(String caption) {
        this.caption = caption;
    }

    // 하위 클래스에서 구현 : concrete 패키지 내에서 구현
    public abstract String makeHTML();
}
