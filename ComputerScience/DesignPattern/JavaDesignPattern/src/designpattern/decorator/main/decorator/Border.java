package designpattern.decorator.main.decorator;

import designpattern.decorator.main.component.Display;

/**
 * Decorator 역할을 하는 추상 클래스
 * - Display 인스턴스를 장식하는 역할
 * - Component 추상 클래스(Display)를 상속받음으로써, 장식과 내용물을 동일시
 * -
 */
public abstract class Border extends Display {
    // 장식을 할 내용물 인스턴스
    protected Display display;

    protected Border(Display display) {
        this.display = display;
    }
}
