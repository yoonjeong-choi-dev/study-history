package designpattern.iterator.main;

// Iterator 구현체
public class BookShelfIterator implements Iterator {
    // 탐색할 컬렌셕 객체 및 현재 인덱스를 위한 필드
    private final BookShelf bookShelf;
    private int curIdx;

    public BookShelfIterator(BookShelf bookShelf) {
        this.bookShelf = bookShelf;
        this.curIdx = 0;
    }


    @Override
    public boolean hasNext() {
        return curIdx < bookShelf.getLength();
    }

    @Override
    public Object next() {
        // 현재 바라보는 객체를 반환하면서, 다음 객체에 대한 인덱스 저장
        Book book = bookShelf.getBook(curIdx);
        curIdx++;
        return book;
    }
}
