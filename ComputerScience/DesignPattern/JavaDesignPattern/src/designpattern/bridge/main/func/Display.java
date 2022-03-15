package designpattern.bridge.main.func;

import designpattern.bridge.main.impl.DisplayImpl;

/**
 * 기능의 클래스 계층의 최상단 클래스
 * - 기능 확장을 위해서는 해당 계층을 상속
 * - 기능 클래스 계층과 구현 클래스 계층 사이의 연결
 * impl 필드
 * - DisplayImpl 추상 클래스는 구현의 클래스 계층의 최상단
 * - 해당 클래스의 하위 클래스 객체를 저장하여 두 계층(기능, 구현) 사이의 bridge 역할
 * - 해당 클래스의 API 기능을 impl 필드의 객체에게 위임
 */
public class Display {
    private final DisplayImpl impl;

    public Display(DisplayImpl impl) {
        this.impl = impl;
    }

    public void open() {
        impl.rawOpen();
    }

    public void print() {
        impl.rawPrint();
    }

    public void close() {
        impl.rawClose();
    }

    public final void display() {
        open();
        print();
        close();
    }
}
