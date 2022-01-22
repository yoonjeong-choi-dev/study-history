package servlets;

import java.io.IOException;

import javax.servlet.ServletContext;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.annotation.WebServlet;

import dao.MemberDao;

@WebServlet("/member/delete")
public class MemberDeleteServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        try {
            // 애플리케이션 컨텍스트 가져오기
            ServletContext sc = getServletContext();
            
            // db 커넥션 가져오기
            //conn = (Connection) sc.getAttribute("conn");
            
            // 컨텍스트에서 가져온 DAO 이용해서 결과 가져오기
            MemberDao dao = (MemberDao)sc.getAttribute("memberDao");
            int ret = dao.delete(Integer.parseInt(request.getParameter("id")));

            String viewPath;
            if (ret != 0) {
                viewPath = "/view/member/MemberDeleteSuccess.jsp";
            } else {
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
}
