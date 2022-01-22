package servlets;

import java.io.IOException;

import javax.servlet.ServletContext;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import javax.servlet.annotation.WebServlet;

import vo.Member;
import dao.MemberDao;

@WebServlet("/auth/login")
public class LoginServlet extends HttpServlet {
    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        RequestDispatcher rs = request.getRequestDispatcher("/view/auth/LoginForm.jsp");
        rs.forward(request, response);
    }

    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        try {
            // 애플리케이션 컨텍스트 가져오기
            ServletContext sc = getServletContext();

            // 컨텍스트에서 가져온 DAO 이용해서 결과 가져오기
            MemberDao dao = (MemberDao)sc.getAttribute("memberDao");
            Member member = dao.login(request.getParameter("email"), request.getParameter("password"));
            
            // 해당 정보가 있으면 로그인 수행
            if(member!= null) {
                // 세션에 저장
                HttpSession session = request.getSession();
                session.setAttribute("member", member);

                // 기본 페이지로 리다이엑트
                response.sendRedirect("../member/list");
            } else {
                // 로그인 실패 페이지로 이동
                RequestDispatcher rd = request.getRequestDispatcher("/view/auth/LoginFail.jsp");
                rd.forward(request, response);
            }
        } catch (Exception ex) {
            // 서버 에러 발생 시, 에러 페이지로 포워딩
            request.setAttribute("error", ex);

            RequestDispatcher rd = request.getRequestDispatcher("/view/ServerError.jsp");
            rd.forward(request, response);
        }
    }
}
