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

@WebServlet("/member/list")
public class MemberListServlet extends HttpServlet {
    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        try {
            // 애플리케이션 컨텍스트 가져오기
            ServletContext sc = getServletContext();
            
            // db 커넥션 가져오기
            //conn = (Connection) sc.getAttribute("conn");
            
            // 컨텍스트에서 가져온 DAO 이용해서 결과 가져오기
            MemberDao dao = (MemberDao)sc.getAttribute("memberDao");

            // 뷰에게 데이터 전달
            request.setAttribute("members", dao.selectList());

            // JSP 출력 위임
            RequestDispatcher rd = request.getRequestDispatcher("/view/member/MemberList.jsp");
            
            // 인클루드 방식 : 위임된 서블릿의 작업이 끝나면 다시 제어권이 돌아옴
            response.setContentType("text/html; charset=UTF-8");    // 인클루드 방식에서는 컨텐츠 타입 설정 필요
            rd.include(request, response);
            
        } catch (Exception ex) {
            //throw new ServletException(ex);

            // 서버 에러 발생 시, 에러 페이지로 포워딩
            request.setAttribute("error", ex);

            RequestDispatcher rd = request.getRequestDispatcher("/view/ServerError.jsp");
            rd.forward(request, response);
        }
    }
}
