package designpattern.abstractfactory.main.factory;

import java.io.FileWriter;
import java.io.IOException;
import java.io.Writer;
import java.util.ArrayList;
import java.util.List;

/**
 * HTML 페이지의 추상화
 * - Factory 추상 클래스가 생성해야 하는 제품에 해당
 * - Factory는 추상 부품(Item -> Tray, Link)을 조립하여 Page 클래스의 추상 객체 생성
 */
public abstract class Page {
    protected String title;
    protected String author;
    protected List<Item> content = new ArrayList<>();

    public Page(String title, String author) {
        this.title = title;
        this.author = author;
    }

    public void add(Item item) {
        content.add(item);
    }

    // 템플릿 메서드
    public final void output() {
        try {
            String filename = title + ".html";

            Writer writer = new FileWriter(filename);
            // 템플릿 메서드 패턴 적용
            writer.write(this.makeHTML());
            writer.close();

            System.out.printf("%s is written\n", filename);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // 템플릿 메서드 패턴에서 템플릿 메서드를 구성하는 추상 메서드
    public abstract String makeHTML();

}
