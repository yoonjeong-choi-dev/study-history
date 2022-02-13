package com.yj.settings;

import lombok.Setter;
import lombok.extern.log4j.Log4j;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import static org.junit.jupiter.api.Assertions.fail;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit.jupiter.SpringExtension;

import javax.sql.DataSource;
import java.sql.Connection;

@ExtendWith(SpringExtension.class)
@ContextConfiguration("file:src/main/webapp/WEB-INF/spring/root-context.xml")
@Log4j
public class DataSourceTest {
    @Setter(onMethod_ = { @Autowired} )
    private DataSource dataSource;

    @Test
    public void testConnection(){
        try (Connection conn = dataSource.getConnection()) {
            log.info("Hikari DataSource Test");
            log.info(conn);
        } catch (Exception ex) {
            fail(ex.getMessage());
        }
    }
}
