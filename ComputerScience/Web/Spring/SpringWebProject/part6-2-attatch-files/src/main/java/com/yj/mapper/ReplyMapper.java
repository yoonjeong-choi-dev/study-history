package com.yj.mapper;

import com.yj.domain.BoardVO;
import com.yj.domain.PageCriteria;
import com.yj.domain.ReplyVO;
import org.apache.ibatis.annotations.Param;

import java.util.List;

public interface ReplyMapper {
    public int insert(ReplyVO vo);

    public ReplyVO selectById(Long id);
    public int getTotalCount(@Param("board_id") Long boardId);
    public List<ReplyVO> selectListWithPage(@Param("cri")PageCriteria cri, @Param("board_id") Long boardId);

    public int update(ReplyVO vo);

    public int delete(Long id);
    void deleteByBoardId(Long boardId);
}
