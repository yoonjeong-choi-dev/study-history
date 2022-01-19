package article.service;

import java.sql.Connection;
import java.sql.SQLException;

import article.dao.ArticleContentDao;
import article.dao.ArticleDao;
import article.model.Article;
import article.model.ArticleContent;
import article.model.ArticleData;
import jdbc.connection.ConnectionProvider;
import jdbc.JdbcUtil;

public class ReadArticleService {
    private ArticleDao articleDao = new ArticleDao();
    private ArticleContentDao contentDao = new ArticleContentDao();

    public ArticleData getArticle(int id, boolean increaseReadCount) {
        Connection conn = null;

        try {
            conn = ConnectionProvider.getConnection();

            Article article = articleDao.selectById(conn, id);
            if (article == null) {
                throw new ArticleNotFoundException();
            }

            ArticleContent content = contentDao.selectById(conn, id);
            if (content == null) {
                throw new ArticleContentNotFoundException();
            }

            if (increaseReadCount) {
                articleDao.increaseReadCount(conn, id);
            }

            return new ArticleData(article, content);
        } catch (SQLException ex) {
            throw new RuntimeException(ex);
        } finally {
            JdbcUtil.close(conn);
        }
    }
}
