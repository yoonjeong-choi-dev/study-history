package designpattern.iterator.main;

// 특정 요소에 대한 클래스
public class Book {
    private final String name;

    public Book(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }
}
