package guestbook.service;

import java.sql.Connection;
import java.sql.SQLException;
import java.lang.IllegalArgumentException;

import guestbook.dao.MessageDao;
import guestbook.model.Message;
import jdbc.JdbcUtil;
import jdbc.connection.ConnectionProvider;

public class WriteMessageService {
    // singleton pattern
    private static WriteMessageService instance = new WriteMessageService();

    public static WriteMessageService getInstance() {
        return instance;
    }

    private WriteMessageService() {
    }

    public void write(Message message) {
        if (message.getGuestName() == null || message.getGuestName().isEmpty()) {
            throw new IllegalArgumentException("invalid guestname");
        }

        Connection conn = null;

        try {
            conn = ConnectionProvider.getConnection();
            MessageDao messageDao = MessageDao.getInstance();
            messageDao.insert(conn, message);
        } catch (SQLException ex) {
            throw new ServiceException("Fail to write message : " + ex.getMessage(), ex);
        } catch (IllegalArgumentException ex) {
            throw new ServiceException("Fail to write message : " + ex.getMessage(), ex);
        } finally {
            JdbcUtil.close(conn);
        }
    }
}
