package designpattern.adapter.main;


// Client 역할 : Target 메서드를 사용하는 일
public class Main {
    public static void main(String[] args) {
        byExtends();
        byDelegate();
    }

    private static void byDelegate() {
        System.out.println("By Delegate");
        // Print 인터페이스 타입 이용 => 객체 생성 이후 코드들은 특정 구현체와 독립적
        Print print = new designpattern.adapter.main.bydelegate.PrintBanner("Hello~");

        // Print 인터페이스를 사용하기 때문에 기존에 제공되는 Banner 클래스의 존재가 코드 상 사라짐
        print.printWeak();
        print.printStrong();
    }

    private static void byExtends() {
        System.out.println("By Extends");
        // Print 인터페이스 타입 이용 => 객체 생성 이후 코드들은 특정 구현체와 독립적
        Print print = new designpattern.adapter.main.byextends.PrintBanner("Hello~");

        // Print 인터페이스를 사용하기 때문에 기존에 제공되는 Banner 클래스의 존재가 코드 상 사라짐
        print.printWeak();
        print.printStrong();
    }
}
