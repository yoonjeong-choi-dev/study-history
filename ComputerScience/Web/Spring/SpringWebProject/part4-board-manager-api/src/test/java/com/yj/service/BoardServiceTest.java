package com.yj.service;

import com.yj.domain.BoardVO;
import com.yj.domain.PageCriteria;
import lombok.Setter;
import lombok.extern.log4j.Log4j;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit.jupiter.SpringExtension;

import static org.junit.jupiter.api.Assertions.*;

@ExtendWith(SpringExtension.class)
@ContextConfiguration("file:src/main/webapp/WEB-INF/spring/root-context.xml")
@Log4j
class BoardServiceTest {

    @Setter(onMethod_ = {@Autowired})
    private BoardService service;

    @Test
    public void testExist() {
        log.info(service);
        assertNotNull(service);
    }

    @Test
    public void testRegister() {
        BoardVO board = new BoardVO();
        board.setTitle("Register Test");
        board.setContent("New Content");
        board.setWriter("YJ-Service-Test");

        service.register(board);
        log.info("New Board Id : " + board.getId());
    }

    @Test
    public void testGetList() {
        service.getList().forEach(board -> log.info(board));
    }

    @Test
    public void testGetListWithPage() {
        PageCriteria cri = new PageCriteria();
        cri.setPageNum(3);
        cri.setNumContents(5);

        log.info("Paging Service Test");
        log.info("start row : " + cri.getStartRow() + ", numContents: " + cri.getNumContents());
        service.getList(cri).forEach(board  -> log.info(board));
    }

    @Test
    public void testGetById() {
        log.info(service.getById(1L));
    }

    @Test
    public void testModify() {
        BoardVO board = service.getById(4L);
        if (board == null) return;

        board.setTitle("Update Service");
        log.info("Modify Result : " + service.modify(board));
    }

    @Test
    public void testRemove() {
        log.info("Remove Result : " + service.remove(6L));
    }
}