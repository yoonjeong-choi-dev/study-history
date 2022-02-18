package com.yj.mapper;

import com.yj.domain.BoardAttachFileVO;

import java.util.List;

public interface BoardAttachFileMapper {
    void insert(BoardAttachFileVO vo);
    void delete(String uuid);
    List<BoardAttachFileVO> selectByBoardId(Long id);

    void deleteByBoardId(Long boardId);

    List<BoardAttachFileVO> getOldFiles();
}
