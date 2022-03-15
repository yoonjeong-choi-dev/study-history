package designpattern.bridge.main.func;

import designpattern.bridge.main.impl.DisplayImpl;

// 기능 계층의 최상단 클래스를 상속받아 기능 추가
public class CountDisplay extends Display {
    public CountDisplay(DisplayImpl impl) {
        super(impl);
    }

    // 새로운 기능 추가
    public void multiDisplay(int times) {
        open();
        for(int i=0;i<times;i++){
            print();
        }
        close();
    }
}
