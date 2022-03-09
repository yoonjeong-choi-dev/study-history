package designpattern.adapter.main;

// 이미 제공되어 있는 클래스
// Adaptee 역할
public class Banner {
    private final String message;

    public Banner(String message) {
        this.message = message;
    }

    public void showWithParen() {
        System.out.printf("(%s)\n", message);
    }

    public void showWithAster() {
        System.out.printf("*%s*\n", message);
    }

}
