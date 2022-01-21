package servlets;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.GenericServlet;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.annotation.WebServlet;

@WebServlet("/calc")
public class CalculotorServlet extends GenericServlet {
    @Override
    public void service(ServletRequest request, ServletResponse response)
            throws IOException, ServletException {
        request.setCharacterEncoding("utf-8");
        PrintWriter out = response.getWriter();

        String operator = request.getParameter("op");
        int v1 = Integer.parseInt(request.getParameter("v1"));
        int v2 = Integer.parseInt(request.getParameter("v2"));

        int result = 0;
        switch (operator) {
            case "+":
                result = v1 + v2;
                break;
            case "-":
                result = v1 - v2;
                break;
            case "*":
                result = v1 * v2;
                break;
            case "/":
                if (v2 == 0) {
                    out.println("0으로 나눌 수 없습니다");
                }
                result = v1 / v2;
                break;
            default:
                out.println("해당 연산을 지원하지 않습니다!");
        }
        out.println(v1 + " " + operator + " " + v2 + " = " + result);
    }
}
