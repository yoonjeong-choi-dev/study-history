package article.service;

import java.util.Map;

import article.model.Writer;

// 쓰기 요청 폼에서 전달한 데이터
public class WriteRequest {
    private Writer writer;
    private String title;
    private String content;

    public WriteRequest(Writer writer, String title, String content) {
        this.writer = writer;
        this.title = title;
        this.content = content;
    }

    public Writer getWriter() {
        return writer;
    }

    public String getTitle() {
        return title;
    }

    public String getContent() {
        return content;
    }

    // 요청 데이터 유효성 검증
    public void validate(Map<String, Boolean> errors) {
        if (title == null || title.trim().isEmpty()) {
            errors.put("title", Boolean.TRUE);
        }
    }
}
