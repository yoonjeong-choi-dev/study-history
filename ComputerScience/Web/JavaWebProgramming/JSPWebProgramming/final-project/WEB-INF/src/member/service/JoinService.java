package member.service;

import java.sql.Connection;
import java.sql.SQLException;
import java.util.Date;

import jdbc.JdbcUtil;
import jdbc.connection.ConnectionProvider;
import member.dao.MemberDao;
import member.model.Member;

public class JoinService {
    private MemberDao memberDao = new MemberDao();

    public void join(JoinRequest joinReq) {
        Connection conn = null;
        try {
            conn = ConnectionProvider.getConnection();
            conn.setAutoCommit(false);

            // Id 중복 확인
            Member member = memberDao.selectById(conn, joinReq.getId());
            if (member != null) {
                JdbcUtil.rollback(conn);
                throw new DuplicateIdException();
            }

            memberDao.insert(conn, new Member(
                    joinReq.getId(), joinReq.getName(), joinReq.getPassword(), new Date()));
            conn.commit();
        } catch (SQLException ex) {
            JdbcUtil.rollback(conn);
            throw new RuntimeException(ex);
        } finally {
            JdbcUtil.close(conn);
        }
    }
}
