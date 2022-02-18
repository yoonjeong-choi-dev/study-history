package com.yj.service;

import com.yj.domain.PageCriteria;
import com.yj.domain.ReplyPageDTO;
import com.yj.domain.ReplyVO;

public interface ReplyService {
    public int register(ReplyVO reply);

    public ReplyVO getById(Long id);
    public ReplyPageDTO getList(PageCriteria cri, Long boardId);
    public int getTotalCount(Long boardId);

    public boolean modify(ReplyVO reply);

    public boolean remove(Long id);
}
