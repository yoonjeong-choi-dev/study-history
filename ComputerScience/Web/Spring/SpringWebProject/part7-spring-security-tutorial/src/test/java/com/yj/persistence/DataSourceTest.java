package com.yj.persistence;

import static org.junit.jupiter.api.Assertions.fail;

import lombok.Setter;
import org.junit.jupiter.api.Test;

import java.sql.Connection;
import javax.sql.DataSource;

import lombok.extern.log4j.Log4j;
import org.junit.jupiter.api.extension.ExtendWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit.jupiter.SpringExtension;

@ExtendWith(SpringExtension.class)
@ContextConfiguration("file:src/main/webapp/WEB-INF/spring/root-context.xml")
@Log4j
public class DataSourceTest {
    @Setter(onMethod_ = { @Autowired })
    private DataSource dataSource;

    @Test
    public void testConnection() {
        try (Connection conn = dataSource.getConnection()) {
            log.info("Hikari DataSource Test");
            log.info(conn);
        } catch(Exception ex) {
            fail(ex.getMessage());
        }
    }
}
