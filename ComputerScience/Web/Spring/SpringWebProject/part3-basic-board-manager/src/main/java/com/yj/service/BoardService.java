package com.yj.service;

import com.yj.domain.BoardVO;

import java.util.List;

public interface BoardService {
    public void register(BoardVO board);

    public BoardVO getById(Long id);
    public List<BoardVO> getList();

    public boolean modify(BoardVO board);

    public boolean remove(Long id);
}
