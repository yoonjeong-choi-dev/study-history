package article.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import jdbc.JdbcUtil;
import article.model.ArticleContent;

public class ArticleContentDao {
    public ArticleContent insert(Connection conn, ArticleContent content)
            throws SQLException {
        PreparedStatement pstmt = null;

        try {
            pstmt = conn.prepareStatement(
                    "insert into article_content " +
                            "(article_id, content) values (?, ?)");
            pstmt.setLong(1, content.getNumber());
            pstmt.setString(2, content.getContent());

            int insertedCount = pstmt.executeUpdate();

            // 저장을 성공한 경우 해당 객체 반환
            if (insertedCount > 0) {
                return content;
            } else {
                return null;
            }
        } finally {
            JdbcUtil.close(pstmt);
        }
    }

    public ArticleContent selectById(Connection conn, int id) throws SQLException {
        PreparedStatement pstmt = null;
        ResultSet rs = null;
        try {
            pstmt = conn.prepareStatement("select * from article_content where article_id = ?");
            pstmt.setInt(1, id);
            rs = pstmt.executeQuery();

            ArticleContent content = null;
            if (rs.next()) {
                content = new ArticleContent(
                        rs.getInt("article_id"), rs.getString("content"));
            }

            return content;
        } finally {
            JdbcUtil.close(rs);
            JdbcUtil.close(pstmt);
        }
    }

    public int update(Connection conn, int id, String content) throws SQLException {
        PreparedStatement pstmt = null;
        try {
            pstmt = conn.prepareStatement("update article_content set content = ? " +
                "where article_id = ?");
            pstmt.setString(1, content);
            pstmt.setInt(2, id);
            return pstmt.executeUpdate();
        } finally {
            JdbcUtil.close(pstmt);
        }
    }

    public int delete(Connection conn, int id) throws SQLException {
        PreparedStatement pstmt = null;
        try {
            pstmt = conn.prepareStatement("delete from article_content where article_id = ?");
            pstmt.setInt(1, id);
            return pstmt.executeUpdate();
        } finally {
            JdbcUtil.close(pstmt);
        }
    }
}
