package guestbook.service;

import java.sql.Connection;
import java.sql.SQLException;

import guestbook.dao.MessageDao;
import guestbook.model.Message;
import jdbc.JdbcUtil;
import jdbc.connection.ConnectionProvider;

public class UpdateMessageService {
    // singleton pattern
    private static UpdateMessageService instance = new UpdateMessageService();

    public static UpdateMessageService getInstance() {
        return instance;
    }

    private UpdateMessageService() {
    }

    public void updateMessage(int messageId, String password, String messageText) {
        Connection conn = null;

        try {
            conn = ConnectionProvider.getConnection();
            // 트랜잭션 시작
            conn.setAutoCommit(false);

            MessageDao messageDao = MessageDao.getInstance();
            Message message = messageDao.select(conn, messageId);

            // 메시지 변경 조건 검사
            if (message == null) {
                throw new MessageNotFoundException("No matched message");
            }
            if (!message.matchPassword(password)) {
                throw new InvalidPassowrdException("bad password");
            }

            // 변경 및 커밋
            messageDao.update(conn, messageId, messageText);
            conn.commit();

        } catch (SQLException ex) {
            JdbcUtil.rollback(conn);
            throw new ServiceException("Fail to update message : " + ex.getMessage(), ex);
        } catch (InvalidPassowrdException | MessageNotFoundException ex) {
            JdbcUtil.rollback(conn);
            throw ex;
        } finally {
            JdbcUtil.close(conn);
        }
    }
}
