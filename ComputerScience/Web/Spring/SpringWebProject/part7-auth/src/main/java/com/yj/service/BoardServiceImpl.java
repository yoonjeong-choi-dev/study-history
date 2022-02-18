package com.yj.service;

import com.yj.domain.BoardAttachFileVO;
import com.yj.domain.BoardVO;
import com.yj.domain.PageCriteria;
import com.yj.mapper.BoardAttachFileMapper;
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
public class BoardServiceImpl implements BoardService {

    @Setter(onMethod_ = @Autowired)
    private BoardMapper mapper;

    @Setter(onMethod_ = @Autowired)
    private BoardAttachFileMapper boardAttachFileMapper;

    @Setter(onMethod_ = @Autowired)
    private ReplyMapper replyMapper;

    @Transactional
    @Override
    public void register(BoardVO board) {
        mapper.insertWithId(board);

        log.info("===========================================");
        log.info("Board Id : " + board.getId());
        log.info("===========================================");

        if(board.getAttachFileList() == null || board.getAttachFileList().size() <= 0){
            return;
        }

        board.getAttachFileList().forEach(file -> {
            file.setBoardId(board.getId());
            boardAttachFileMapper.insert(file);
        });
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
    public int getTotalCount(PageCriteria cri) {
        return mapper.getTotalCount(cri);
    }

    @Override
    public boolean modify(BoardVO board) {

        boardAttachFileMapper.deleteByBoardId(board.getId());

        boolean modifyResult = mapper.update(board) == 1;

        board.getAttachFileList().forEach(file -> {
            file.setBoardId(board.getId());
            boardAttachFileMapper.insert(file);
        });

        return modifyResult;
    }

    @Transactional
    @Override
    public boolean remove(Long id) {
        replyMapper.deleteByBoardId(id);
        boardAttachFileMapper.deleteByBoardId(id);
        return mapper.delete(id) == 1;
    }

    @Override
    public List<BoardAttachFileVO> getAttachList(Long id) {
        return boardAttachFileMapper.selectByBoardId(id);
    }
}
