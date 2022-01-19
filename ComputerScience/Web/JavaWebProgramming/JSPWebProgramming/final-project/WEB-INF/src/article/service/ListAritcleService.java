package article.service;

import java.sql.Connection;
import java.sql.SQLException;
import java.util.List;


import article.dao.ArticleDao;
import article.model.Article;
import jdbc.JdbcUtil;
import jdbc.connection.ConnectionProvider;

public class ListAritcleService {
    private ArticleDao articleDao = new ArticleDao();
    private int sizePerPage = 10;

    // pageNum에 해당하는 게시글 목록 반환
    public ArticlePage getArticlePage(int pageNum) {
        Connection conn = null;
        try {
            conn = ConnectionProvider.getConnection();
            int totalCount = articleDao.selectCount(conn);

            int startPage = (pageNum-1) * sizePerPage;
            if(startPage > totalCount) {
                // 맨 마지막 페이지로
                pageNum = totalCount / sizePerPage;
                if (pageNum % sizePerPage > 0) 
                    pageNum++;
                
                startPage = (pageNum-1) * sizePerPage;
            }

            List<Article> articleList = articleDao.select(conn, startPage, sizePerPage);

            return new ArticlePage(totalCount, pageNum, sizePerPage, articleList);
        } catch (SQLException ex) {
            throw new RuntimeException(ex);
        } finally {
            JdbcUtil.close(conn);
        }
    }
}
