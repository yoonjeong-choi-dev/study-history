package listeners;

import javax.servlet.ServletContext;
import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;

import dao.MemberDao;

// DataSource로 변경
//import util.DBConnectionPool;
import org.apache.commons.dbcp2.BasicDataSource;

public class ContextLoader implements ServletContextListener {
    //Connection conn;
    //DBConnectionPool connPool;
    BasicDataSource ds;

    @Override
    public void contextInitialized(ServletContextEvent event) {
        try {
            ServletContext sc = event.getServletContext();

            // jdbc 드라이버 로드
            String driver = sc.getInitParameter("driver");

            // db 연결 정보를 컨텍스트 초기화 매개변수를 통해 가져온다
            String url = sc.getInitParameter("url");
            String user = sc.getInitParameter("user");
            String password = sc.getInitParameter("password");

            //connPool = new DBConnectionPool(driver, url, user, password);
            ds = new BasicDataSource();
            ds.setDriverClassName(driver);
            ds.setUrl(url);
            ds.setUsername(user);
            ds.setPassword(password);

            // Dao 생성 및 커넥션 설정
            MemberDao dao = new MemberDao();
            dao.setDataSource(ds);
            //dao.setConnection(conn);
            //dao.setDbConnectionPool(connPool);

            // 애플리케이션 컨텍스트에 dao 저장
            sc.setAttribute("memberDao", dao);
        } catch (Throwable ex) {
            ex.printStackTrace();
        }
    }

    @Override
    public void contextDestroyed(ServletContextEvent event) {
        // 커넥션 해제
        try {
            //conn.close();
            //connPool.closeAll();
            if (ds != null) ds.close();
        } catch (Exception ex) { }
    }
}
