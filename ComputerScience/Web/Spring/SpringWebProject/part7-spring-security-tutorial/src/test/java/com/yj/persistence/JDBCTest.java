package com.yj.persistence;

import static org.junit.jupiter.api.Assertions.fail;
import org.junit.jupiter.api.Test;

import java.sql.Connection;
import java.sql.DriverManager;

import lombok.extern.log4j.Log4j;

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
        String url = "jdbc:mysql://localhost:3306/spring5web?" + "useUnicode=true&characterEncoding=utf8";
        String user = "spring5webuser";
        String password = "spring5webuser";
        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            log.info(conn);
        } catch (Exception ex) {
            fail(ex.getMessage());
        }
    }
}
