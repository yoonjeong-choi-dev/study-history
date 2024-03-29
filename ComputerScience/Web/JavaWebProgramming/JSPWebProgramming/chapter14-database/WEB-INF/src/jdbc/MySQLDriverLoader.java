package jdbc;

import javax.servlet.http.HttpServlet;
import javax.servlet.ServletConfig;
import javax.servlet.ServletException;

public class MySQLDriverLoader extends HttpServlet {
    // 어플리케이션 시작 시 한번만 실행되는 함수
    public void init(ServletConfig config) throws ServletException {
        try {
            Class.forName("com.mysql.jdbc.Driver");
        } catch(Exception ex) {
            throw new ServletException(ex);
        }
    }
}
