package com.yj.domain;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

@Getter
@Setter
@ToString
public class PageCriteria {
    private int pageNum;
    private int numContents;

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
}
