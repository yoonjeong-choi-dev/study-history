package mvc.simple;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class SimpleController extends HttpServlet {
    // 1단계 : HTTP 요청 받기
    @Override
    public void doGet(HttpServletRequest request, HttpServletResponse response)
        throws ServletException, IOException {
        processRequest(request, response);
    }

    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response)
        throws ServletException, IOException {
        processRequest(request, response);
    }

    private void processRequest(HttpServletRequest request, HttpServletResponse response)
        throws IOException, ServletException {

        // 2단계 : 요청 파악
        String type = request.getParameter("type");

        // 3단계 : 요청한 기능 수행
        Object resultObject = null;
        if (type == null || type.equals("greeting")) {
            resultObject = "안녕하세요";
        } else if (type.equals("date")) {
            resultObject = new java.util.Date();
        } else {
            resultObject = "Invalid Type";
        }

        // 4단계 : 결과를 request/session 객체에 저장
        request.setAttribute("result", resultObject);

        // 5단계 : 알맞은 뷰로 포워딩
        RequestDispatcher dispatcher = request.getRequestDispatcher("/simpleView.jsp");
        dispatcher.forward(request, response);
    }
}
