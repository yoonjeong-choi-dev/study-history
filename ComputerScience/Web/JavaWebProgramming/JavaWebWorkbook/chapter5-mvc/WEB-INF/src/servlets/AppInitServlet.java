package servlets;

import java.sql.Connection;
import java.sql.DriverManager;

import javax.servlet.ServletConfig;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;

public class AppInitServlet extends HttpServlet {
    @Override
    public void init(ServletConfig config) throws ServletException {
        System.out.println("AppInitSevlet Init...");
        super.init(config);

        try {
            ServletContext sc = getServletContext();

            // jdbc 드라이버 로드
            Class.forName(sc.getInitParameter("driver"));

            // db 연결 정보를 컨텍스트 초기화 매개변수를 통해 가져온다
            String url = sc.getInitParameter("url");
            String user = sc.getInitParameter("user");
            String password = sc.getInitParameter("password");

            Connection conn = DriverManager.getConnection(url, user, password);
            sc.setAttribute("conn", conn);
        } catch (Throwable ex) {
            throw new ServletException(ex);
        }
    }

    @Override
    public void destroy() {
        System.out.println("AppInitSevlet Stop...");
        super.destroy();

        Connection conn = (Connection) getServletContext().getAttribute("conn");

        try {
            if (conn != null && conn.isClosed() == false) {
                conn.close();
            }
        } catch (Exception ex) {

        }
    }
}
