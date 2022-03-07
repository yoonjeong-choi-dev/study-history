package designpattern.iterator.main;

public class Main {
    public static void main(String[] args) {
        BookShelf bookShelf = new BookShelf(4);
        bookShelf.appendBook(new Book("Around the world in 80 Days"));
        bookShelf.appendBook(new Book("Bible"));
        bookShelf.appendBook(new Book("Cinderella"));
        bookShelf.appendBook(new Book("Daddy-Long-Legs"));

        // 이터레이터 패턴 사용
        // => 아래 코드는 BookShelf 클래스라는 특정 구현에 의존하지 않는 코드
        // i.e BookShelf 클래스 내부 변경(배열을 리스트 or 큐에 저장)에 대해서 독립적
        Iterator itr = bookShelf.iterator();
        while(itr.hasNext()){
            Book book = (Book) itr.next();
            System.out.println(book.getName());
        }
    }
}
