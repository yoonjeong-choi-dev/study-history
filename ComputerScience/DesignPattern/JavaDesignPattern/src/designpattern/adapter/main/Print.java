package designpattern.adapter.main;

// Client 가 사용할 메서드를 제공
// Target 역할 i.e Adaptee 가 제공하는 기능을 사용하여 Client가 필요한 메서드를 제공하는 역할
public interface Print {
    void printWeak();

    void printStrong();
}
