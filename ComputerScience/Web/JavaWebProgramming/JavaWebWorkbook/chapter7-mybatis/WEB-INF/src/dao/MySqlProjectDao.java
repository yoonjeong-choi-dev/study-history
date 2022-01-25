package dao;

import java.util.HashMap;
import java.util.Hashtable;
import java.util.List;

// import java.util.Date;
// import java.util.ArrayList;

// import java.sql.Connection;
// import java.sql.ResultSet;
// import java.sql.Statement;
// import java.sql.PreparedStatement;

// myBatis 적용
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;

// import javax.sql.DataSource;

import annotation.Component;
import vo.Project;

@Component("projectDao")
public class MySqlProjectDao implements ProjectDao {
    // DataSource connPool;
    // public void setDataSource(DataSource ds) {
    // this.connPool = ds;
    // }

    SqlSessionFactory sqlSessionFactory;

    public void setSqlSessionFactory(SqlSessionFactory sqlSessionFactory) {
        this.sqlSessionFactory = sqlSessionFactory;
    }

    @Override
    public List<Project> selectList(HashMap<String, Object> paramMap) throws Exception {
        SqlSession sqlSession = sqlSessionFactory.openSession();

        try {
            return sqlSession.selectList("dao.ProjectDao.selectList", paramMap);
        } finally {
            sqlSession.close();
        }
        // Connection conn = null;
        // Statement stmt = null;
        // ResultSet rs = null;

        // try {
        // conn = connPool.getConnection();
        // stmt = conn.createStatement();
        // rs = stmt.executeQuery("select * from projects order by created_date desc");

        // ArrayList<Project> projects = new ArrayList<Project>();
        // while(rs.next()) {
        // projects.add(new Project()
        // .setId(rs.getInt("id"))
        // .setTitle(rs.getString("title"))
        // .setStartDate(rs.getDate("start_date"))
        // .setEndDate(rs.getDate("end_date"))
        // .setState(rs.getInt("state")));
        // }
        // return projects;
        // } catch (Exception ex) {
        // throw ex;
        // } finally {
        // if (rs != null) {
        // try {rs.close();} catch (Exception e) {};
        // }

        // if (stmt != null) {
        // try {stmt.close();} catch (Exception e) {};
        // }

        // if(conn != null) conn.close();
        // }
    }

    @Override
    public Project selectById(int id) throws Exception {
        SqlSession sqlSession = sqlSessionFactory.openSession();

        try {
            return sqlSession.selectOne("dao.ProjectDao.selectById", id);
        } finally {
            sqlSession.close();
        }

        // Connection conn = null;
        // Statement stmt = null;
        // ResultSet rs = null;

        // try {
        // conn = connPool.getConnection();
        // stmt = conn.createStatement();
        // rs = stmt.executeQuery("select * from projects where id=" + id);

        // if (rs.next()) {
        // return new Project()
        // .setId(rs.getInt("id"))
        // .setTitle(rs.getString("title"))
        // .setStartDate(rs.getDate("start_date"))
        // .setEndDate(rs.getDate("end_date"))
        // .setContent(rs.getString("content"))
        // .setCreatedDate(rs.getDate("created_date"))
        // .setState(rs.getInt("state"))
        // .setTags(rs.getString("tags"));
        // } else {
        // return null;
        // }

        // } catch (Exception ex) {
        // throw ex;
        // } finally {
        // if (rs != null) {
        // try {rs.close();} catch (Exception e) {};
        // }

        // if (stmt != null) {
        // try {stmt.close();} catch (Exception e) {};
        // }

        // if(conn != null) conn.close();
        // }
    }

    @Override
    public int insert(Project project) throws Exception {
        SqlSession sqlSession = sqlSessionFactory.openSession();

        try {
            int count = sqlSession.insert("dao.ProjectDao.insert", project);
            sqlSession.commit();
            return count;
        } finally {
            sqlSession.close();
        }
        // Connection conn = null;
        // PreparedStatement stmt = null;

        // try {
        // conn = connPool.getConnection();
        // stmt = conn.prepareStatement(
        // "insert into projects
        // (title,content,start_date,end_date,state,created_date,tags) " +
        // "values (?, ?, ?, ?, 0, now(), ?)"
        // );

        // stmt.setString(1, project.getTitle());
        // stmt.setString(2, project.getContent());
        // stmt.setDate(3, toSqlDate(project.getStartDate()));
        // stmt.setDate(4, toSqlDate(project.getEndDate()));
        // stmt.setString(5, project.getTags());

        // return stmt.executeUpdate();

        // } catch (Exception ex) {
        // throw ex;
        // } finally {

        // if (stmt != null) {
        // try {stmt.close();} catch (Exception e) {};
        // }

        // if(conn != null) conn.close();
        // }
    }

    @Override
    public int update(Project project) throws Exception {
        SqlSession sqlSession = sqlSessionFactory.openSession();

        try {
            Project original = sqlSession.selectOne("dao.ProjectDao.selectById", project.getId());

            // 변경되어야 하는 부분만 저장
            Hashtable<String, Object> paramMap = new Hashtable<String, Object>();
            if (!project.getTitle().equals(original.getTitle())) {
                paramMap.put("title", project.getTitle());
            }
            if (!project.getContent().equals(original.getContent())) {
                paramMap.put("content", project.getContent());
            }
            if (project.getStartDate().compareTo(original.getStartDate()) != 0) {
                paramMap.put("startDate", project.getStartDate());
            }
            if (project.getEndDate().compareTo(original.getEndDate()) != 0) {
                paramMap.put("endDate", project.getEndDate());
            }
            if (project.getState() != original.getState()) {
                paramMap.put("state", project.getState());
            }
            if (!project.getTags().equals(original.getTags())) {
                paramMap.put("tags", project.getTags());
            }

            if(paramMap.size() > 0) {
                paramMap.put("id", project.getId());
                int count = sqlSession.update("dao.ProjectDao.update", paramMap);
                sqlSession.commit();
                return count;
            } else {
                return 0;
            }
        } finally {
            sqlSession.close();
        }
        // Connection conn = null;
        // PreparedStatement stmt = null;

        // try {
        // conn = connPool.getConnection();
        // stmt = conn.prepareStatement(
        // "update projects set " +
        // "title=?, " +
        // "content=?, " +
        // "start_date=?, " +
        // "end_date=?, " +
        // "state=?, " +
        // "tags=? " +
        // "where id=?"
        // );

        // stmt.setString(1, project.getTitle());
        // stmt.setString(2, project.getContent());
        // stmt.setDate(3, toSqlDate(project.getStartDate()));
        // stmt.setDate(4, toSqlDate(project.getEndDate()));
        // stmt.setInt(5, project.getState());
        // stmt.setString(6, project.getTags());
        // stmt.setInt(7, project.getId());

        // return stmt.executeUpdate();

        // } catch (Exception ex) {
        // throw ex;
        // } finally {
        // if (stmt != null) {
        // try {stmt.close();} catch (Exception e) {};
        // }

        // if(conn != null) conn.close();
        // }
    }

    @Override
    public int delete(int id) throws Exception {
        SqlSession sqlSession = sqlSessionFactory.openSession();

        try {
            int count = sqlSession.delete("dao.ProjectDao.delete", id);
            sqlSession.commit();
            return count;
        } finally {
            sqlSession.close();
        }
        // Connection conn = null;
        // Statement stmt = null;

        // try {
        // conn = connPool.getConnection();
        // stmt = conn.createStatement();
        // return stmt.executeUpdate("delete from projects where id=" + id);
        // } catch (Exception ex) {
        // throw ex;
        // } finally {
        // if (stmt != null) {
        // try {stmt.close();} catch (Exception e) {};
        // }

        // if(conn != null) conn.close();
        // }
    }

    // private java.sql.Date toSqlDate(Date date) {
    // return new java.sql.Date(date.getTime());
    // }
}
