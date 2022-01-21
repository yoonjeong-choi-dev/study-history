package servlets;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.GenericServlet;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;

public class CalculatorServlet extends GenericServlet {
    @Override
    public void service(ServletRequest request, ServletResponse response)
            throws IOException, ServletException {
        int a = Integer.parseInt(request.getParameter("a"));
        int b = Integer.parseInt(request.getParameter("b"));

        response.setContentType("text/plain");
        response.setCharacterEncoding("utf-8");
        PrintWriter writer = response.getWriter();

        writer.println("a= " + a + ", b =" + b);
        writer.println("a + b = " + (a + b));
        writer.println("a - b = " + (a - b));
        writer.println("a * b = " + (a * b));
        writer.println("a / b = " + ((float) a / (float) b));
        writer.println("a % b = " + (a % b));
    }
}
