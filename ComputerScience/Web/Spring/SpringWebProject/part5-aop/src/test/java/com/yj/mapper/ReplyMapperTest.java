package com.yj.mapper;

import com.yj.domain.PageCriteria;
import com.yj.domain.ReplyVO;
import lombok.Setter;
import lombok.extern.log4j.Log4j;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit.jupiter.SpringExtension;

import java.util.List;
import java.util.stream.IntStream;

@ExtendWith(SpringExtension.class)
@ContextConfiguration("file:src/main/webapp/WEB-INF/spring/root-context.xml")
@Log4j
public class ReplyMapperTest {

    // 테스트를 위해 외래키 board_id 미리 지정
    private Long[] boardIdArr = {1L, 2L, 4L, 8L, 9L};

    @Setter(onMethod_ = {@Autowired})
    private ReplyMapper mapper;

    @Test
    public void testMapper() {
        log.info(mapper);
    }

    @Test
    public void testInsert() {
        IntStream.rangeClosed(1, 10).forEach(i -> {
            ReplyVO vo = new ReplyVO();

            vo.setBoardId(boardIdArr[i % 5]);
            vo.setReply("Reply Insert Test " + i);
            vo.setReplier("MapperTest" + i);

            mapper.insert(vo);
        });
    }

    @Test
    public void testSelectById() {
        ReplyVO result = mapper.selectById(3L);

        log.info("Select By Id Test");
        log.info(result);
    }

    @Test
    public void testTotalCount() {
        int total = mapper.getTotalCount(boardIdArr[2]);

        log.info(String.format("Total Count with board %d : %d", boardIdArr[2], total));
    }

    @Test
    public void testUpdate() {
        Long targetId = 3L;
        ReplyVO vo = mapper.selectById(targetId);

        vo.setReply("Test Update!");
        int ret = mapper.update(vo);

        log.info("Update Test : " + ret);
    }

    @Test
    public void testDelete() {
        Long targetId = 10L;

        int ret = mapper.delete(targetId);
        log.info("Delete Test : " + ret);
    }

    @Test
    public void addDummyForTest() {
        Long targetId = 1L;
        IntStream.rangeClosed(1, 100).forEach(i -> {
            ReplyVO vo = new ReplyVO();

            vo.setBoardId(targetId);
            vo.setReply("Last Page Test Data" + i);
            vo.setReplier("MapperTester" + i);

            mapper.insert(vo);
        });
    }

    @Test
    public void testPage() {
        PageCriteria cri = new PageCriteria(1, 10);
        List<ReplyVO> replies = mapper.selectListWithPage(cri, 1L);

        log.info("Page Test");
        replies.forEach(reply-> log.info(reply));
    }
}
