package guestbook.service;

import java.sql.Connection;
import java.sql.SQLException;
import java.util.Collections;
import java.util.List;

import guestbook.dao.MessageDao;
import guestbook.model.Message;
import jdbc.JdbcUtil;
import jdbc.connection.ConnectionProvider;

public class GetMessageListService {
    // singleton pattern
    private static GetMessageListService instance = new GetMessageListService();

    public static GetMessageListService getInstance() {
        return instance;
    }

    private GetMessageListService() {
    }

    private static final int MESSAGE_COUNT_PER_PAGE = 3;

    public MessageListView getMessageList(int pageNumber) {
        Connection conn = null;
        int currentPageNumber = pageNumber;

        try {
            conn = ConnectionProvider.getConnection();
            MessageDao messageDao = MessageDao.getInstance();

            int messageTotalCount = messageDao.selectCount(conn);

            List<Message> messageList = null;
            int startRow = 0, endRow = 0;

            if (messageTotalCount > 0) {
                startRow = (pageNumber - 1) * MESSAGE_COUNT_PER_PAGE + 1;
                endRow = startRow + MESSAGE_COUNT_PER_PAGE - 1;
                messageList = messageDao.selectList(conn, startRow, endRow);
            } else {
                currentPageNumber = 0;
                messageList = Collections.emptyList();
            }

            return new MessageListView(messageList, messageTotalCount, currentPageNumber, MESSAGE_COUNT_PER_PAGE, startRow, endRow);
        } catch (SQLException ex) {
            throw new ServiceException("Fail to get list : " + ex.getMessage(), ex);
        } finally {
            JdbcUtil.close(conn);
        }
    }
}
