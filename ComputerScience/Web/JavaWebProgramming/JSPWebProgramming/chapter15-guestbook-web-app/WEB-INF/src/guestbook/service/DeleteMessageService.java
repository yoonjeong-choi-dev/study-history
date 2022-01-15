package guestbook.service;

import java.sql.Connection;
import java.sql.SQLException;

import guestbook.dao.MessageDao;
import guestbook.model.Message;
import jdbc.JdbcUtil;
import jdbc.connection.ConnectionProvider;

public class DeleteMessageService {
    // singleton pattern
    private static DeleteMessageService instance = new DeleteMessageService();

    public static DeleteMessageService getInstance() {
        return instance;
    }

    private DeleteMessageService() {
    }

    public void deleteMessage(int messageId, String password) {
        Connection conn = null;

        try {
            conn = ConnectionProvider.getConnection();
            // 트랜잭션 시작
            conn.setAutoCommit(false);

            MessageDao messageDao = MessageDao.getInstance();
            Message message = messageDao.select(conn, messageId);

            // 메시지 삭제 조건 검사
            if (message == null) {
                throw new MessageNotFoundException("No matched message");
            }
            if (!message.matchPassword(password)) {
                throw new InvalidPassowrdException("bad password");
            }

            // 삭제 및 커밋
            messageDao.delete(conn, messageId);
            conn.commit();

        } catch (SQLException ex) {
            JdbcUtil.rollback(conn);
            throw new ServiceException("Fail to delete message : " + ex.getMessage(), ex);
        } catch (InvalidPassowrdException | MessageNotFoundException ex) {
            JdbcUtil.rollback(conn);
            throw ex;
        } finally {
            JdbcUtil.close(conn);
        }
    }
}
