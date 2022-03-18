package designpattern.decorator.main.component;

/**
 * Component 역할을 하는 추상 클래스
 * - 기능을 추가할 때 핵심이 되는 역할
 * - 장식을 하는 대상이 되는 내용물에 해당
 * - 장식을 위한 원시 오브젝트를 생성하는 API 정의
 */
public abstract class Display {
    public abstract int getColumns();

    public abstract int getRows();

    public abstract String getRowText(int row);

    // 템플릿 메서드 역할
    public final void show() {
        for (int i = 0; i < getRows(); i++) {
            System.out.println(getRowText(i));
        }
    }
}
