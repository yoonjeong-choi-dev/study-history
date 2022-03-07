package designpattern.iterator.main;

import java.util.ArrayList;
import java.util.List;

// Aggregate 구현체
public class BookShelf implements Aggregate {
    // Book 객체들을 저장하는 컨테이너의 형태는 Aggregate 인터페이스에 의해서 추상화
    private final List<Book> books;

    public BookShelf(int capacity) {
        books = new ArrayList<>(capacity);
    }

    public Book getBook(int idx) {
        return books.get(idx);
    }

    public void appendBook(Book book) {
        books.add(book);
    }

    public int getLength() {
        return books.size();
    }

    @Override
    public Iterator iterator() {
        return new BookShelfIterator(this);
    }
}
