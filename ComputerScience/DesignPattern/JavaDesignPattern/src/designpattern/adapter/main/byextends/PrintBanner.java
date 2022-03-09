package designpattern.adapter.main.byextends;

import designpattern.adapter.main.Banner;
import designpattern.adapter.main.Print;

// 상속을 이용하여 Banner -> Print 연결
// Adapter 역할 : Adaptee 역할의 메서드를 사용하여 Target 역할을 만족시키도록 변환하는 역할
public class PrintBanner extends Banner implements Print {

    public PrintBanner(String message) {
        super(message);
    }

    @Override
    public void printWeak() {
        showWithParen();
    }

    @Override
    public void printStrong() {
        showWithAster();
    }
}
