package com.yj.domain;

import lombok.Data;

import java.util.Date;
import java.util.List;

@Data
public class BoardVO {
    private long id;
    private String title;
    private String content;
    private String writer;
    private Date registeredDate;
    private Date modifiedDate;

    private int replyCount;

    private List<BoardAttachFileVO> attachFileList;
}
