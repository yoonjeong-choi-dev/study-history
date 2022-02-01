package com.yj.mapper;

import com.yj.domain.BoardVO;

import java.util.List;

public interface BoardMapper {
    public List<BoardVO> selectList();
    public BoardVO selectById(Long id);

    public void insert(BoardVO board);
    public Integer insertWithId(BoardVO board);

    public int update(BoardVO board);

    public int delete(Long id);
}
