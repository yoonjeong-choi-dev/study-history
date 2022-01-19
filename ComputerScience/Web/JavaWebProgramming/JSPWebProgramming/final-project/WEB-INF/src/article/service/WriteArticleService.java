package article.service;

import java.sql.Connection;
import java.sql.SQLException;
import java.util.Date;

import article.dao.ArticleContentDao;
import article.dao.ArticleDao;
import article.model.Article;
import article.model.ArticleContent;
import jdbc.JdbcUtil;
import jdbc.connection.ConnectionProvider;

public class WriteArticleService {
    private ArticleDao articleDao = new ArticleDao();
    private ArticleContentDao contentDao = new ArticleContentDao();

    public Integer write(WriteRequest req) {
        Connection conn = null;
        try {
            conn = ConnectionProvider.getConnection();
            conn.setAutoCommit(false);
            
            // 요청으로부터 Article 객체 생성 및 저장
            Article article = toArticle(req);
            Article savedArticle = articleDao.insert(conn, article);
            if (savedArticle == null) {
                throw new RuntimeException("Fail to insert the article");
            }

            ArticleContent content = new ArticleContent(savedArticle.getNumber(), req.getContent());
            ArticleContent savedContent = contentDao.insert(conn, content);
            if(savedContent == null) {
                throw new RuntimeException("Fail to insert the article content");
            }

            conn.commit();

            return savedArticle.getNumber();
        } catch (SQLException ex) {
            JdbcUtil.rollback(conn);
            throw new RuntimeException(ex);
        } catch (RuntimeException ex) {
            JdbcUtil.rollback(conn);
            throw ex;
        } finally {
            JdbcUtil.close(conn);
        }
    }

    public Article toArticle(WriteRequest req) {
        Date now = new Date();
        return new Article(null, req.getWriter(), req.getTitle(), now, now, 0);
    }
}
