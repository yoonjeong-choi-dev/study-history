package listeners;

import javax.servlet.ServletContext;
import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;

//import org.apache.commons.dbcp2.BasicDataSource;
// import javax.naming.InitialContext;
// import javax.sql.DataSource;

// import dao.MySqlMemberDao;
// import controls.LoginController;
// import controls.LogoutController;
// import controls.MemberAddController;
// import controls.MemberDeleteController;
// import controls.MemberListController;
// import controls.MemberUpdateController;

import context.ApplicationContext;


public class ContextLoader implements ServletContextListener {

    static ApplicationContext applicationContext;

    public static ApplicationContext getApplicationContext() {
        return applicationContext;
    }

    @Override
    public void contextInitialized(ServletContextEvent event) {
        try {
            ServletContext sc = event.getServletContext();

            String propertiesPath = sc.getRealPath(sc.getInitParameter("contextConfigLocation"));
            applicationContext = new ApplicationContext(propertiesPath);

            // InitialContext initialContext = new InitialContext();
            // DataSource ds = (DataSource)initialContext.lookup(
            //     "java:comp/env/jdbc/javaweb");

            // Dao 생성 및 커넥션 설정
            // MySqlMemberDao dao = new MySqlMemberDao();
            // dao.setDataSource(ds);

            // 애플리케이션 컨텍스트에 dao 저장 : 별도로 꺼내서 사용하지 않음 (의존성 주입 사용)
            // sc.setAttribute("memberDao", dao);

            // dao 객체를 컨트롤러로 주입
            // sc.setAttribute("/auth/login.do", 
            //     new LoginController().setMemberDao(dao));
            // sc.setAttribute("/auth/logout.do", new LogoutController());
            // sc.setAttribute("/member/list.do", 
            //     new MemberListController().setMemberDao(dao));
            // sc.setAttribute("/member/add.do", 
            //     new MemberAddController().setMemberDao(dao));
            // sc.setAttribute("/member/update.do", 
            //     new MemberUpdateController().setMemberDao(dao));
            // sc.setAttribute("/member/delete.do", 
            //     new MemberDeleteController().setMemberDao(dao));
        } catch (Throwable ex) {
            ex.printStackTrace();
        }
    }

    @Override
    public void contextDestroyed(ServletContextEvent event) { }
}
