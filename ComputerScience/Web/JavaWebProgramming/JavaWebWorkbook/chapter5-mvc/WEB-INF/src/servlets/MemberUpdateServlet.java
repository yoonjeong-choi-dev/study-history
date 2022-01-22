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

@WebServlet("/member/update")
public class MemberUpdateServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        try {
            // 애플리케이션 컨텍스트 가져오기
            ServletContext sc = getServletContext();

            // 컨텍스트에서 가져온 DAO 이용해서 결과 가져오기
            MemberDao dao = (MemberDao)sc.getAttribute("memberDao");
            Member member = dao.selectById(Integer.parseInt(request.getParameter("id")));

            String viewPath;
            if(member!= null) {
                request.setAttribute("member", member);
                viewPath = "/view/member/MemberUpdate.jsp";
            } else {
                // 에러 저장
                request.setAttribute("error", "일치하는 회원이 없습니다");
                viewPath = "/view/ClientError.jsp";
            }
            RequestDispatcher rd = request.getRequestDispatcher(viewPath);
            rd.forward(request, response);
        } catch (Exception ex) {
            // 서버 에러 발생 시, 에러 페이지로 포워딩
            request.setAttribute("error", ex);

            RequestDispatcher rd = request.getRequestDispatcher("/view/ServerError.jsp");
            rd.forward(request, response);
        }
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
                .setId(Integer.parseInt(request.getParameter("id")))
                .setEmail(request.getParameter("email"))
                .setName(request.getParameter("name"));
            
            dao.update(member);
            
            RequestDispatcher rd = request.getRequestDispatcher("/view/member/MemberUpdateSuccess.jsp");
            rd.forward(request, response);
        } catch (Exception ex) {
            // 서버 에러 발생 시, 에러 페이지로 포워딩
            request.setAttribute("error", ex);

            RequestDispatcher rd = request.getRequestDispatcher("/view/ServerError.jsp");
            rd.forward(request, response);
        }
    }
}
