package designpattern.prototype.main;

import designpattern.prototype.main.framework.Manager;
import designpattern.prototype.main.framework.Product;
import designpattern.prototype.main.proto.MessageBox;
import designpattern.prototype.main.proto.UnderlinePen;

public class Main {
    public static void main(String[] args) {
        // 복제할 프로토타입 인스턴스들을 생성하고 등록
        Manager manager = new Manager();

        UnderlinePen underlinePen = new UnderlinePen('-');
        MessageBox messageBox1 = new MessageBox('*');
        MessageBox messageBox2 = new MessageBox('/');

        manager.register("strong message", underlinePen);
        manager.register("warning message", messageBox1);
        manager.register("slash box", messageBox2);

        // Manager 객체를 이용하여 특정 프로토타입 인스턴스 복사하여 생성
        Product p1 = manager.create("strong message");
        p1.use("Hello World!");

        Product p2 = manager.create("warning message");
        p2.use("Hello World!");

        Product p3 = manager.create("slash box");
        p3.use("Hello World!");
    }
}
