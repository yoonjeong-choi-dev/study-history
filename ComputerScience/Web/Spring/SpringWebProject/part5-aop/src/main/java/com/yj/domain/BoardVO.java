package com.yj.domain;

import lombok.Data;

import java.util.Date;

@Data
public class BoardVO {
    private long id;
    private String title;
    private String content;
    private String writer;
    private Date registeredDate;
    private Date modifiedDate;
}
