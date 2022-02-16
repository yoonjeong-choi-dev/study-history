package com.yj.mapper;


import com.yj.domain.MemberVO;
import lombok.Setter;
import lombok.extern.log4j.Log4j;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit.jupiter.SpringExtension;

@ExtendWith(SpringExtension.class)
@ContextConfiguration({
        "file:src/main/webapp/WEB-INF/spring/root-context.xml"
})
@Log4j
class MemberMapperTest {
    @Setter(onMethod_ = @Autowired)
    private MemberMapper mapper;

    @Test
    public void testRead() {
        MemberVO vo = mapper.read("admin90");
        log.info(vo);
        vo.getAuthList().forEach(auth -> log.info(auth));
    }
}