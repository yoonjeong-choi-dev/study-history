package member.service;

import java.sql.Connection;
import java.sql.SQLException;

import jdbc.JdbcUtil;
import jdbc.connection.ConnectionProvider;
import member.dao.MemberDao;
import member.model.Member;

public class ChangePasswordService {
    private MemberDao memberDao = new MemberDao();

    public void changePassword(String userId, String curPw, String newPw) {
        Connection conn = null;
        try {
            conn = ConnectionProvider.getConnection();
            conn.setAutoCommit(false);

            // 계정이 있는지 확인
            Member member = memberDao.selectById(conn, userId);
            if (member == null) {
                JdbcUtil.rollback(conn);
                throw new MemberNotFoundException();
            }

            // 비밀번호가 일치하는지 확인
            if (!member.matchPassword(curPw)) {
                JdbcUtil.rollback(conn);
                throw new InvalidPasswordException();
            }

            // 비밀번호 변경
            member.changePassword(newPw);

            memberDao.update(conn, member);
            conn.commit();
        } catch (SQLException ex) {
            JdbcUtil.rollback(conn);
            throw new RuntimeException(ex);
        } finally {
            JdbcUtil.close(conn);
        }
    }
}
