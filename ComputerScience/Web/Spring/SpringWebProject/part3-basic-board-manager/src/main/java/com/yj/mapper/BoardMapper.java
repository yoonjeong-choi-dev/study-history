package com.yj.mapper;

import com.yj.domain.BoardVO;
import com.yj.domain.PageCriteria;

import java.util.List;

public interface BoardMapper {
    public List<BoardVO> selectList();
    public BoardVO selectById(Long id);
    public List<BoardVO> selectListWithPage(PageCriteria cri);

    public void insert(BoardVO board);
    public Integer insertWithId(BoardVO board);

    public int update(BoardVO board);

    public int delete(Long id);
}
