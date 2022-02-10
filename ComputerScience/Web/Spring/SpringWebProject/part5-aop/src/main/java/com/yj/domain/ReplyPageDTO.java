package com.yj.domain;

import lombok.AllArgsConstructor;
import lombok.Getter;

import java.util.List;


@AllArgsConstructor
@Getter
public class ReplyPageDTO {
    private int numReplies;
    private List<ReplyVO> replies;
}
