package com.yj.domain;

import lombok.Data;

@Data
public class BoardAttachFileVO {
    private String uuid;
    private String uploadPath;
    private String fileName;
    private int isImage;
    private Long boardId;
}
