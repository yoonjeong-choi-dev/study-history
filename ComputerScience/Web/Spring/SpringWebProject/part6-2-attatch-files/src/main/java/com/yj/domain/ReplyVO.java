package com.yj.domain;

import java.util.Date;

//import com.fasterxml.jackson.annotation.JsonFormat;
import lombok.Data;

@Data
public class ReplyVO {
    private Long id;
    private Long boardId;
    private String reply;
    private String replier;

    //@JsonFormat(shape = JsonFormat.Shape.STRING, pattern = "yyyy-MM-dd HH:mm")
    private Date registeredDate;

    //@JsonFormat(shape = JsonFormat.Shape.STRING, pattern = "yyyy-MM-dd HH:mm")
    private Date modifiedDate;
}
