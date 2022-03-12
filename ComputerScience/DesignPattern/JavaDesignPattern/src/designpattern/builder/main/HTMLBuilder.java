package designpattern.builder.main;

import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class HTMLBuilder extends Builder {
    private String filename;
    private PrintWriter writer;

    @Override
    public void buildTitle(String title) {
        // 타이틀을 이용하여 파일명 생성
        filename = title + ".html";
        try {
            writer = new PrintWriter(new FileWriter(filename));
        } catch (IOException e) {
            e.printStackTrace();
        }

        writer.println(String.format("<html><head><title>%s</title></head><body>", title));
        writer.println(String.format("<h1>%s</h1>", title));
    }

    @Override
    public void buildString(String string) {
        writer.println(String.format("<p>%s</p>", string));
    }

    @Override
    public void buildItems(String[] items) {
        writer.println("<ul>");
        for (String item : items) {
            writer.println(String.format("<li>%s</li>", item));
        }
        writer.println("</ul>");
    }

    @Override
    public void buildClose() {
        writer.println("</body></html>");
        writer.close();
    }

    public String getFilename() {
        return filename;
    }
}
