package article.dao;

import java.sql.Connection;
import java.sql.Statement;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;
import java.util.Date;
import java.util.ArrayList;
import java.util.List;

import jdbc.JdbcUtil;
import article.model.Article;
import article.model.Writer;

public class ArticleDao {

    public Article insert(Connection conn, Article article) throws SQLException {
        PreparedStatement pstmt = null;
        Statement stmt = null;
        ResultSet rs = null;

        try {
            pstmt = conn.prepareStatement("insert into article "
                    + "(writer_id, writer_name, title, registered_date, modified_date, read_count) "
                    + "values (?, ?, ?, ?, ?, 0)");
            pstmt.setString(1, article.getWriter().getId());
            pstmt.setString(2, article.getWriter().getName());
            pstmt.setString(3, article.getTitle());
            pstmt.setTimestamp(4, toTimestamp(article.getRegisteredDate()));
            pstmt.setTimestamp(5, toTimestamp(article.getModifiedDate()));

            int insertedCount = pstmt.executeUpdate();

            // 저장을 성공한 경우
            if (insertedCount > 0) {
                // 마지막 저장한 게시글 데이터 반환
                stmt = conn.createStatement();
                rs = stmt.executeQuery("select last_insert_id() from article");

                if (rs.next()) {
                    Integer num = rs.getInt(1);
                    return new Article(num,
                            article.getWriter(),
                            article.getTitle(),
                            article.getRegisteredDate(),
                            article.getModifiedDate(),
                            0);
                }
            }
            return null;
        } finally {
            JdbcUtil.close(rs);
            JdbcUtil.close(stmt);
            JdbcUtil.close(pstmt);
        }
    }

    public int selectCount(Connection conn) throws SQLException {
        Statement stmt = null;
        ResultSet rs = null;
        try {
            stmt = conn.createStatement();
            rs = stmt.executeQuery("select count(*) from article");
            if (rs.next()) {
                return rs.getInt(1);
            }
            return 0;
        } finally {
            JdbcUtil.close(rs);
            JdbcUtil.close(stmt);
        }
    }

    public List<Article> select(Connection conn, int startRow, int size)
            throws SQLException {
        PreparedStatement pstmt = null;
        ResultSet rs = null;
        try {
            pstmt = conn.prepareStatement(
                    "select * from article order by article_id desc limit ?,?");
            pstmt.setInt(1, startRow);
            pstmt.setInt(2, size);
            rs = pstmt.executeQuery();

            List<Article> result = new ArrayList<>();
            while (rs.next()) {
                result.add(convertArticle(rs));
            }

            return result;
        } finally {
            JdbcUtil.close(rs);
            JdbcUtil.close(pstmt);
        }
    }

    public Article selectById(Connection conn, int id) throws SQLException {
        PreparedStatement pstmt = null;
        ResultSet rs = null;
        try {
            pstmt = conn.prepareStatement("select * from article where article_id = ?");
            pstmt.setInt(1, id);
            rs = pstmt.executeQuery();
            
            Article article = null;
            if (rs.next()) {
                article = convertArticle(rs);
            } 

            return article;
        } finally {
            JdbcUtil.close(rs);
            JdbcUtil.close(pstmt);
        }
    }

    public int update(Connection conn, int id, String title) throws SQLException {
        PreparedStatement pstmt = null;
        try {
            pstmt = conn.prepareStatement("update article set title= ?, modified_date = now() " +
                "where article_id = ?");
            pstmt.setString(1, title);
            pstmt.setInt(2, id);
            return pstmt.executeUpdate();
        } finally {
            JdbcUtil.close(pstmt);
        }
    }

    public int delete(Connection conn, int id) throws SQLException {
        PreparedStatement pstmt = null;
        try {
            pstmt = conn.prepareStatement("delete from article where article_id = ?");
            pstmt.setInt(1, id);
            return pstmt.executeUpdate();
        } finally {
            JdbcUtil.close(pstmt);
        }
    }

    public void increaseReadCount(Connection conn, int id) throws SQLException {
        PreparedStatement pstmt = null;
        try {
            pstmt = conn.prepareStatement(
                "update article set read_count = read_count + 1 " + 
                "where article_id = ?");
            pstmt.setInt(1, id);
            pstmt.executeUpdate();
        } finally {
            JdbcUtil.close(pstmt);
        }
    }

    private Timestamp toTimestamp(Date date) {
        return new Timestamp(date.getTime());
    }

    private Date toDate(Timestamp timestamp) {
        return new Date(timestamp.getTime());
    }

    private Article convertArticle(ResultSet rs) throws SQLException {
        return new Article (
            rs.getInt("article_id"),
            new Writer(rs.getString("writer_id"), rs.getString("writer_name")),
            rs.getString("title"),
            toDate(rs.getTimestamp("registered_date")),
            toDate(rs.getTimestamp("modified_date")),
            rs.getInt("read_count")
        );
    }
}
