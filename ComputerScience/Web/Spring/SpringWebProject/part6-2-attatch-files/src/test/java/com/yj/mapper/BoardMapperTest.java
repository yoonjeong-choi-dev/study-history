package com.yj.mapper;

import com.yj.domain.BoardVO;
import com.yj.domain.PageCriteria;
import lombok.Setter;
import lombok.extern.log4j.Log4j;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit.jupiter.SpringExtension;

import java.util.List;

@ExtendWith(SpringExtension.class)
@ContextConfiguration("file:src/main/webapp/WEB-INF/spring/root-context.xml")
@Log4j
class BoardMapperTest {
    @Setter(onMethod_ = {@Autowired})
    private BoardMapper mapper;

    @Test
    void testSelectList() {
        log.info("Select List Test");
        mapper.selectList().forEach(board-> log.info(board));
    }

    @Test
    void testInsert() {
        BoardVO board = new BoardVO();
        board.setTitle("Insert Test");
        board.setContent("New Content without id");
        board.setWriter("YJ-Test");

        mapper.insert(board);

        log.info("Insert Test : Check the id");
        log.info(board);
    }

    @Test
    void makePageTestDummyData() {
        for(int i= 1;i<=30;i++) {
            String dummy = "Paging Test Data " + i;
            BoardVO board = new BoardVO();
            board.setTitle(dummy);
            board.setContent(dummy);
            board.setWriter(dummy);

            mapper.insert(board);
            log.info(board);
        }
    }

    @Test
    void testInsertWithId() {
        BoardVO board = new BoardVO();
        board.setTitle("Insert With Id Test");
        board.setContent("New Content with id");
        board.setWriter("YJ-Test");

        mapper.insertWithId(board);

        log.info("Insert With Test : Check the id");
        log.info(board);
    }

    @Test
    void testSelectById() {
        BoardVO result = mapper.selectById(5L);

        log.info("Select By Id Test");
        log.info(result);
    }

    @Test
    void testDelete() {
        log.info("Delete Test");
        log.info("Delete Count : " + mapper.delete(3L));
    }

    @Test
    void testUpdate() {
        BoardVO board = new BoardVO();
        board.setId(5L);
        board.setTitle("Update Test");
        board.setContent("Update Content~~~~");
        board.setWriter("Update YJ");

        int count = mapper.update(board);

        log.info("Update Test");
        log.info("Update Count : " + count);
    }

    @Test
    void testPaging() {
        PageCriteria cri = new PageCriteria();
        cri.setPageNum(3);
        cri.setNumContents(5);

        log.info("Paging Mapper Test");
        log.info("start row : " + cri.getStartRow() + ", numContents: " + cri.getNumContents());
        mapper.selectListWithPage(cri).forEach(board-> log.info(board));
    }


    @Test
    void testSearch1() {
        PageCriteria cri = new PageCriteria();
        cri.setKeyword("Paging Test");

        List<BoardVO> list = mapper.selectListWithPage(cri);
        list.forEach(board -> log.info(board));
    }

    @Test
    void testSearch2() {
        PageCriteria cri = new PageCriteria();
        cri.setKeyword("Paging Test");
        cri.setType("W");

        List<BoardVO> list = mapper.selectListWithPage(cri);
        list.forEach(board -> log.info(board));
    }

    @Test
    void testSearch3() {
        PageCriteria cri = new PageCriteria();
        cri.setKeyword("Paging Test");
        cri.setType("TC");

        List<BoardVO> list = mapper.selectListWithPage(cri);
        list.forEach(board -> log.info(board));
    }

    @Test
    void testSearch4() {
        PageCriteria cri = new PageCriteria();
        cri.setKeyword("Empty");
        cri.setType("TC");

        List<BoardVO> list = mapper.selectListWithPage(cri);
        list.forEach(board -> log.info(board));
    }

}