package designpattern.facade.main.component;

import java.io.IOException;
import java.io.Writer;

/**
 * 간단한 HTML 페이지를 작성하는 컴포넌트
 * - 제약 조건 : title 메서드를 처음에 한번 불러야 함
 * - 제약 조건들에 대해서는 퍼사드 역할을 하는 클래스에서 인지하고 사용해야 한다
 */
public class HtmlWriter {
    private final Writer writer;

    public HtmlWriter(Writer writer) {
        this.writer = writer;
    }

    public void title(String title) throws IOException {
        writer.write("<html><head><title>");
        writer.write(title);
        writer.write("</title></head>");

        writer.write("<body>\n");
        writer.write(String.format("<h1>%s</h1>", title));
    }

    public void paragraph(String message) throws IOException {
        writer.write(String.format("<p>%s</p>\n", message));
    }

    public void link(String href, String caption) throws IOException {
        paragraph(String.format("<a href=\"%s\"> %s </a>", href, caption));
    }

    public void mailTo(String mailAddress, String username) throws IOException {
        link(String.format("mailto:%s", mailAddress), username);
    }

    public void close() throws IOException {
        writer.write("</body></html>\n");
        writer.close();
    }
}
