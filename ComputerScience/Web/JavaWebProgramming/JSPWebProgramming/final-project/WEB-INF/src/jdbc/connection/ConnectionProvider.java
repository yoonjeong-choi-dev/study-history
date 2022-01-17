package jdbc.connection;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

// 커넥션 풀에서 커넥션 객체를 가져오는 유틸 클래스
public class ConnectionProvider {
    public static Connection getConnection() throws SQLException {
        // 커넥션 풀에서 정의한 커넥션 풀 이름
        return DriverManager.getConnection("jdbc:apache:commons:dbcp:board");
    }
}
