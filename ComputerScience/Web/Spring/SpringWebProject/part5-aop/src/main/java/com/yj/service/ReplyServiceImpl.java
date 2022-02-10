package com.yj.service;

import com.yj.domain.PageCriteria;
import com.yj.domain.ReplyPageDTO;
import com.yj.domain.ReplyVO;
import com.yj.mapper.BoardMapper;
import com.yj.mapper.ReplyMapper;
import lombok.Setter;
import lombok.extern.log4j.Log4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

@Service
@Log4j
public class ReplyServiceImpl implements ReplyService{

    @Setter(onMethod_ = @Autowired)
    private ReplyMapper mapper;

    @Setter(onMethod_ = @Autowired)
    private BoardMapper boardMapper;

    @Transactional
    @Override
    public int register(ReplyVO reply) {
        boardMapper.updateReplyCount(reply.getBoardId(), 1);
        return mapper.insert(reply);
    }

    @Override
    public ReplyVO getById(Long id) {
        return mapper.selectById(id);
    }

    @Override
    public ReplyPageDTO getList(PageCriteria cri, Long boardId) {
        return new ReplyPageDTO(
                getTotalCount(boardId),
                mapper.selectListWithPage(cri, boardId)
        );
    }

    @Override
    public int getTotalCount(Long boardId) {
        return mapper.getTotalCount(boardId);
    }

    @Override
    public boolean modify(ReplyVO reply) {
        return mapper.update(reply) == 1;
    }

    @Transactional
    @Override
    public boolean remove(Long id) {
        ReplyVO reply = mapper.selectById(id);
        boardMapper.updateReplyCount(reply.getBoardId(), -1);

        return mapper.delete(id) == 1;
    }
}
