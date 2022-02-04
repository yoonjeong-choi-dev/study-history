package com.yj.service;

import com.yj.domain.BoardVO;
import com.yj.domain.PageCriteria;

import java.util.List;

public interface BoardService {
    public void register(BoardVO board);

    public BoardVO getById(Long id);
    public List<BoardVO> getList();
    public List<BoardVO> getList(PageCriteria cri);
    public int getTotalCount();

    public boolean modify(BoardVO board);

    public boolean remove(Long id);
}
