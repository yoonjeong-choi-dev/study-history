package com.yj.domain;

import lombok.Data;

@Data
public class UploadFileDTO {
    private String fileName;
    private String uploadPath;
    private String uuid;
    private int isImage;
}
