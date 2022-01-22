package servlets;

import java.io.IOException;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.RequestDispatcher;

import vo.Member;
import dao.MemberDao;

@WebServlet("/member/add")
public class MemberAddServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        RequestDispatcher rs = request.getRequestDispatcher("/view/member/MemberAdd.jsp");
        rs.forward(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        try {
            // 애플리케이션 컨텍스트 가져오기
            ServletContext sc = getServletContext();

            // 컨텍스트에서 가져온 DAO 이용해서 결과 가져오기
            MemberDao dao = (MemberDao)sc.getAttribute("memberDao");
            Member member = new Member()
                .setEmail(request.getParameter("email"))
                .setPassword(request.getParameter("password"))
                .setName(request.getParameter("name"));
            dao.insert(member);

            // 쿼리 결과 응답 => 기본 페이지로 리다이렉트
            response.sendRedirect("list");

        } catch (Exception ex) {
            // 서버 에러 발생 시, 에러 페이지로 포워딩
            request.setAttribute("error", ex);

            RequestDispatcher rd = request.getRequestDispatcher("/view/ServerError.jsp");
            rd.forward(request, response);
        }
    }
}
