package designpattern.adapter.main.bydelegate;

import designpattern.adapter.main.Banner;
import designpattern.adapter.main.Print;

// Banner 클래스를 위임하여 Banner -> Print 연결
// Adapter 역할 : Adaptee 역할의 메서드를 사용하여 Target 역할을 만족시키도록 변환하는 역할
public class PrintBanner implements Print {
    // 위임할 객체
    private final Banner banner;

    public PrintBanner(String message) {
        // 생성자를 통해 위임할 객체 생성
        banner = new Banner(message);
    }

    @Override
    public void printWeak() {
        banner.showWithParen();
    }

    @Override
    public void printStrong() {
        banner.showWithAster();
    }
}
