package servlets;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.sql.PreparedStatement;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class MemberUpdateServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        Connection conn = null;
        Statement stmt = null;
        ResultSet rs = null;

        try {
            // jdbc 드라이버 로드
            Class.forName(getInitParameter("driver"));
            
            // db 연결 정보를 서블릿 초기화 매개변수를 통해 가져온다
            String url = getInitParameter("url");
            String user = getInitParameter("user");
            String password = getInitParameter("password");

            // db 연결 및 쿼리
            conn = DriverManager.getConnection(url, user, password);
            stmt = conn.createStatement();
            rs = stmt.executeQuery("select * from members where id=" + request.getParameter("id"));
            rs.next();

            // 쿼리 결과 응답
            response.setContentType("text/html; charset=UTF-8");
            PrintWriter out = response.getWriter();
            out.println("<html><head><title>회원 정보</title></head>");
            out.println("<h1>회원 정보</h1>");
            out.println("<form action='update' method='post'>");
            out.println("번호: <input type='text' name='id' value='" +
				request.getParameter("id") + "' readonly><br>");
            out.println("이름: <input type='text' name='name'" +
				" value='" + rs.getString("name")  + "'><br>");
            out.println("이메일: <input type='text' name='email'" +
				" value='" + rs.getString("email")  + "'><br>");
			out.println("가입일: " + rs.getDate("created_date") + "<br>");
			out.println("<input type='submit' value='변경하기'>");
			out.println("<input type='button' value='삭제' "
					+ "onclick='location.href=\"delete?id=" + 
					request.getParameter("id") + "\";'>");
			out.println("<input type='button' value='취소'" + 
				" onclick='location.href=\"list\"'>");
			out.println("</form>");
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

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        //request.setCharacterEncoding("utf-8");
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            // jdbc 드라이버 로드
            Class.forName(getInitParameter("driver"));
            
            // db 연결 정보를 서블릿 초기화 매개변수를 통해 가져온다
            String url = getInitParameter("url");
            String user = getInitParameter("user");
            String password = getInitParameter("password");

            // db 연결 및 쿼리
            conn = DriverManager.getConnection(url, user, password);
            pstmt = conn.prepareStatement(
                "update members set email=?, name=?, modified_date=now() " +
                "where id=?"
            );
            pstmt.setString(1, request.getParameter("email"));
            pstmt.setString(2, request.getParameter("name"));
            pstmt.setInt(3, Integer.parseInt(request.getParameter("id")));
            pstmt.executeUpdate();

            // 쿼리 결과 응답 결과 출력 및 1초후 기본 페이지로(리프레시)
            response.setContentType("text/html; charset=UTF-8");
            PrintWriter out = response.getWriter();
            out.println("<html><head><title>수정 완료</title></head>");
            out.println("<h1>회원정보를 수정했습니다!</h1>");
            out.println("</body></html>");
            response.addHeader("Refresh", "1;url=list");
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
