package com.yj.domain;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;
import org.springframework.web.util.UriComponentsBuilder;

@Getter
@Setter
@ToString
public class PageCriteria {
    private int pageNum;
    private int numContents;

    private String type;
    private String keyword;

    public PageCriteria() {
        this(1, 10);
    }

    public PageCriteria(int pageNum, int numContents) {
        this.pageNum = Math.max(pageNum, 1);
        this.numContents = Math.max(numContents, 1);
    }

    // for mysql limit
    public int getStartRow() {
        return (pageNum -1 ) * numContents;
    }

    public String[] getTypeArr() {
        return type == null ? new String[] {} : type.split("");
    }

    // URI Builder
    public String getListLink() {
        UriComponentsBuilder builder = UriComponentsBuilder.fromPath("")
                .queryParam("pageNum", pageNum)
                .queryParam("numContents", numContents)
                .queryParam("type", type)
                .queryParam("keyword", keyword);

        return builder.toUriString();
    }
}
