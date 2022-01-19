package article.service;

import java.sql.Connection;
import java.sql.SQLException;

import article.dao.ArticleContentDao;
import article.dao.ArticleDao;
import article.model.Article;
import jdbc.JdbcUtil;
import jdbc.connection.ConnectionProvider;

public class DeleteArticleService {
    private ArticleDao articleDao = new ArticleDao();
	private ArticleContentDao contentDao = new ArticleContentDao();

	public void delete(String userId, int id) {
		Connection conn = null;
		try {
			conn = ConnectionProvider.getConnection();
			conn.setAutoCommit(false);
			
			Article article = articleDao.selectById(conn, id);
			if (article == null) {
				throw new ArticleNotFoundException();
			}
			if (!canModify(userId, article)) {
				throw new PermissionDeniedException();
			}
			articleDao.delete(conn, id);
			contentDao.delete(conn, id);
			conn.commit();
		} catch (SQLException e) {
			JdbcUtil.rollback(conn);
			throw new RuntimeException(e);
		} catch (PermissionDeniedException e) {
			JdbcUtil.rollback(conn);
			throw e;
		} finally {
			JdbcUtil.close(conn);
		}
	}

	private boolean canModify(String userId, Article article) {
		// 사용자가 작성한 게시글인지 확인
		return article.getWriter().getId().equals(userId);
	}
}
