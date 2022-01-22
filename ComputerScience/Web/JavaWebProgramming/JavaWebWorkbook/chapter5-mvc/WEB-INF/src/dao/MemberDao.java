package dao;

import java.util.ArrayList;
import java.util.List;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.Statement;
import java.sql.PreparedStatement;

import vo.Member;
//import util.DBConnectionPool; 
import javax.sql.DataSource;

public class MemberDao {
    DataSource connPool;

    public void setDataSource(DataSource ds) {
        this.connPool = ds;
    }
    //DBConnectionPool connPool;

    // public void setDbConnectionPool(DBConnectionPool connPool) {
    //     this.connPool = connPool;
    // }
    // private Connection conn;

    // public void setConnection(Connection conn) {
    //     this.conn = conn;
    // }

    public List<Member> selectList() throws Exception {
        Connection conn = null;
        Statement stmt = null;
        ResultSet rs = null;

        try {
            // db 연결 및 쿼리
            conn = connPool.getConnection();
            stmt = conn.createStatement();
            rs = stmt.executeQuery("select * from members order by modified_date desc");

            // 쿼리 결과를 vo 리스트에 저장
            ArrayList<Member> members = new ArrayList<Member>();
            while (rs.next()) {
                members.add(new Member()
                    .setId(rs.getInt("id"))
                    .setName(rs.getString("name"))
                    .setEmail(rs.getString("email"))
                    .setCreatedDate(rs.getDate("created_date")));
            }
            return members;
        } catch (Exception e) {
            throw e;
        } finally {
            if (rs != null) {
                try {rs.close();} catch (Exception e) {};
            }

            if (stmt != null) {
                try {stmt.close();} catch (Exception e) {};
            }
                        
            if(conn != null) conn.close();
        }
    }

    public Member selectById(int id) throws Exception {
        Connection conn = null;
        Statement stmt = null;
        ResultSet rs = null;

        try {
            conn = connPool.getConnection();
            stmt = conn.createStatement();
            rs = stmt.executeQuery("select * from members where id=" + id);
            if (rs.next()) {
                return new Member()
                .setId(rs.getInt("id"))
                .setEmail(rs.getString("email"))
                .setName(rs.getString("name"))
                .setCreatedDate(rs.getDate("created_date"));
            } else {
                return null;
            }
        } catch (Exception ex) {
            throw ex;
        } finally {
            if (rs != null) {
                try {rs.close();} catch (Exception e) {};
            }

            if (stmt != null) {
                try {stmt.close();} catch (Exception e) {};
            }
                        
            if(conn != null) conn.close();
        }
        
    }

    public Member login(String email, String password) throws Exception {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            conn = connPool.getConnection();
            pstmt = conn.prepareStatement("select name, email from members where email=? and password = ?");
            pstmt.setString(1, email);
            pstmt.setString(2, password);

            rs = pstmt.executeQuery();

            if (rs.next()) {
                return new Member()
                    .setEmail(rs.getString("email"))
                    .setName(rs.getString("name"));
            } else {
                return null;
            }
        } catch (Exception e) {
            throw e;
        } finally {
            if (rs != null) {
                try {rs.close();} catch (Exception e) {};
            }

            if (pstmt != null) {
                try {pstmt.close();} catch (Exception e) {};
            }
                        
            if(conn != null) conn.close();
        }
    }

    public int insert(Member member) throws Exception {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            conn = connPool.getConnection();
            pstmt = conn.prepareStatement(
                "insert into members(email,password, name,created_date, modified_date) " + 
                "values (?, ?, ?,now(),now());"
            );
            pstmt.setString(1, member.getEmail());
            pstmt.setString(2, member.getPassword());
            pstmt.setString(3, member.getName());

            return pstmt.executeUpdate();
        } catch (Exception ex) {
            throw ex;
        } finally {
            if (rs != null) {
                try {rs.close();} catch (Exception e) {};
            }

            if (pstmt != null) {
                try {pstmt.close();} catch (Exception e) {};
            }

            if(conn != null) conn.close();
        }
    }

    public int update(Member member) throws Exception {
        Connection conn = null;
        PreparedStatement pstmt = null;

        try {
            conn = connPool.getConnection();
            pstmt = conn.prepareStatement(
                "update members set email=?, name=?, modified_date=now() " +
                "where id=?"
            );
            pstmt.setString(1, member.getEmail());
            pstmt.setString(2, member.getName());
            pstmt.setInt(3, member.getId());
            return pstmt.executeUpdate();
        } catch (Exception e) {
            throw e;
        } finally {
            if (pstmt != null) {
                try {pstmt.close();} catch (Exception e) {};
            }

            if(conn != null) conn.close();
        }
        
    }

    public int delete(int id) throws Exception {
        Connection conn = null;
        PreparedStatement pstmt = null;

        try {
            conn = connPool.getConnection();
            pstmt = conn.prepareStatement("delete from members where id=?");
            pstmt.setInt(1, id);
            return pstmt.executeUpdate();
        } catch (Exception e) {
            throw e;
        } finally {
            if (pstmt != null) {
                try {pstmt.close();} catch (Exception e) {};
            }

            if(conn != null) conn.close();
        }
    }
}
