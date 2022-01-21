package servlets;

import java.io.IOException;
import java.io.PrintWriter;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.PreparedStatement;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.annotation.WebServlet;

@WebServlet("/member/delete")
public class MemberDeleteServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        //request.setCharacterEncoding("utf-8");
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            // 컨텍스트 초기화 매변수에 접근하기 위한 서블릿 컨텍스트 객체 반환
            ServletContext sc = getServletContext();
            // jdbc 드라이버 로드
            Class.forName(sc.getInitParameter("driver"));
            
            // db 연결 정보를 컨텍스트 초기화 매개변수를 통해 가져온다
            String url = sc.getInitParameter("url");
            String user = sc.getInitParameter("user");
            String password = sc.getInitParameter("password");

            // db 연결 및 쿼리
            conn = DriverManager.getConnection(url, user, password);
            pstmt = conn.prepareStatement("delete from members where id=?");
            pstmt.setInt(1, Integer.parseInt(request.getParameter("id")));
            pstmt.executeUpdate();

            // 쿼리 결과 응답 결과 출력 및 1초후 기본 페이지로(리프레시)
            response.setContentType("text/html; charset=UTF-8");
            PrintWriter out = response.getWriter();
            out.println("<html><head><title>삭제 완료</title></head>");
            out.println("<h1>회원정보를 삭제했습니다!</h1>");
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
