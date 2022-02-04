package com.yj.service;

import com.yj.domain.BoardVO;
import com.yj.domain.PageCriteria;
import com.yj.mapper.BoardMapper;
import lombok.Setter;
import lombok.extern.log4j.Log4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
@Log4j
public class BoardServiceImpl implements BoardService {

    @Setter(onMethod_ = @Autowired)
    private BoardMapper mapper;

    @Override
    public void register(BoardVO board) {
        mapper.insertWithId(board);
    }

    @Override
    public BoardVO getById(Long id) {
        return mapper.selectById(id);
    }

    @Override
    public List<BoardVO> getList() {
        return mapper.selectList();
    }

    @Override
    public List<BoardVO> getList(PageCriteria cri) {
        return mapper.selectListWithPage(cri);
    }

    @Override
    public int getTotalCount() {
        return mapper.getTotalCount();
    }

    @Override
    public boolean modify(BoardVO board) {
        return mapper.update(board) == 1;
    }

    @Override
    public boolean remove(Long id) {
        return mapper.delete(id) == 1;
    }
}
