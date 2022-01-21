package servlets;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

import javax.servlet.GenericServlet;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.annotation.WebServlet;

@WebServlet("/member/list")
public class MemberListServlet extends GenericServlet {
    @Override
    public void service(ServletRequest reqeust, ServletResponse response)
            throws ServletException, IOException {
        Connection conn = null;
        Statement stmt = null;
        ResultSet rs = null;

        try {
            DriverManager.registerDriver(new com.mysql.jdbc.Driver());

            // db 연결 정보
            String url = "jdbc:mysql://localhost:3306/javawebworkbook?" +
                    "useUnicode=true&characterEncoding=utf8";
            String user = "javawebuser";
            String password = "javawebuser";

            // db 연결 및 쿼리
            conn = DriverManager.getConnection(url, user, password);
            stmt = conn.createStatement();
            rs = stmt.executeQuery("select * from members order by modified_date desc");

            // 쿼리 결과 응답
            response.setContentType("text/html; charset=UTF-8");
            PrintWriter out = response.getWriter();
            out.println("<html><head><title>회원 목록</title></head>");
            out.println("<h1>회원 목록</h1>");
            out.println("<p><a href='add'>회원 가입</a></p>");

            while (rs.next()) {
                out.println(
                        rs.getInt("id") + ", " +
                        "<a href='update?id=" + rs.getInt("id") + "'> "
                        + rs.getString("name") + "</a>, " + 
                        rs.getString("email") + ", " +
                        rs.getDate("created_date") + "<hr>");
                
            }
            out.println("</body></html>");
        } catch (Exception ex) {
            throw new ServletException(ex);
        } finally {
            if (rs != null) {
                try {rs.close();} catch (Exception e) {};
            }

            if (stmt != null) {
                try {stmt.close();} catch (Exception e) {};
            }

            if (conn != null) {
                try {conn.close();} catch (Exception e) {};
            }
        }
    }
}
