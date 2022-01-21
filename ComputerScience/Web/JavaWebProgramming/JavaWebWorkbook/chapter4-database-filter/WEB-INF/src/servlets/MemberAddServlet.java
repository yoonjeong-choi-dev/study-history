package servlets;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.PreparedStatement;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/member/add")
public class MemberAddServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html; charset=utf-8");

        PrintWriter out = response.getWriter();

        out.println("<html><head><title>회원 가입</title></head>");
        out.println("<h1>회원 가입</h1>");
        out.println("<form action='add' method='POST'>");
        out.println("이름 : <input type='text' name='name'> <br>");
        out.println("이메일 : <input type='text' name='email'> <br>");
        out.println("비밀번호 : <input type='password' name='password'> <br>");
        out.println("<input type='submit' value='가입'>");
        out.println("<input type='reset' value='취소'>");
        out.println("</form>");
        out.println("</body></html>");
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        //request.setCharacterEncoding("utf-8");
        Connection conn = null;
        PreparedStatement pstmt = null;
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
            pstmt = conn.prepareStatement(
                "insert into members(email,password, name,created_date, modified_date) " + 
                "values (?, ?, ?,now(),now());"
            );
            pstmt.setString(1, request.getParameter("email"));
            pstmt.setString(2, request.getParameter("password"));
            pstmt.setString(3, request.getParameter("name"));
            pstmt.executeUpdate();

            // 쿼리 결과 응답 결과 출력
            // response.setContentType("text/html; charset=UTF-8");
            // PrintWriter out = response.getWriter();
            // out.println("<html><head><title>가입 완료</title></head>");
            // out.println("<h1>가입 완료!</h1>");
            // out.println("<p><a href='list'>회원 목록</a></p>");
            // out.println("</body></html>");

            // 쿼리 결과 응답 => 기본 페이지로 리다이렉트
            response.sendRedirect("list");

        } catch (Exception ex) {
            throw new ServletException(ex);
        } finally {
            if (rs != null) {
                try {rs.close();} catch (Exception e) {};
            }

            if (pstmt != null) {
                try {pstmt.close();} catch (Exception e) {};
            }

            if (conn != null) {
                try {conn.close();} catch (Exception e) {};
            }
        }
    }
}
