package article.model;

import java.util.Date;

public class Article {
    private Integer number;
    private Writer writer;
    private String title;
    private Date registeredDate;
    private Date modifiedDate;
    private int readCount;

    public Article(Integer number, Writer writer, String title,
            Date registeredDate, Date modifiedDate, int readCount) {
        this.number = number;
        this.writer = writer;
        this.title = title;
        this.registeredDate = registeredDate;
        this.modifiedDate = modifiedDate;
        this.readCount = readCount;
    }

    public Integer getNumber() {
		return number;
	}

	public Writer getWriter() {
		return writer;
	}

	public String getTitle() {
		return title;
	}

	public Date getRegisteredDate() {
		return registeredDate;
	}

	public Date getModifiedDate() {
		return modifiedDate;
	}

	public int getReadCount() {
		return readCount;
	}
}
