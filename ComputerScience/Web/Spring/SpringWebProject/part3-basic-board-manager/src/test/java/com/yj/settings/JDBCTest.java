package com.yj.settings;

import lombok.extern.log4j.Log4j;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.fail;

import java.sql.Connection;
import java.sql.DriverManager;

@Log4j
public class JDBCTest {
    static {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    @Test
    public void testConnection() {
        String url = "jdbc:log4jdbc:mysql://localhost:3306/spring5web?useUnicode=true&characterEncoding=utf8";
        String user = "spring5webuser";
        String pw = "spring5webuser";

        try (Connection conn = DriverManager.getConnection(url, user, pw)) {
            log.info(conn);
        } catch (Exception ex) {
            fail(ex.getMessage());
        }
    }
}
