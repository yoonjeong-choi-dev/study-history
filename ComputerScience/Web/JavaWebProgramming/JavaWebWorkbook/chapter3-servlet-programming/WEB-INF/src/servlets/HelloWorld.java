package servlets;

import java.io.IOException;
import javax.servlet.Servlet;
import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;

// 
public class HelloWorld implements Servlet {
    ServletConfig config;

    @Override
    public void init(ServletConfig config) throws ServletException {
        System.out.println("init() called");
        this.config = config;
    }

    @Override
    public void destroy() {
        System.out.println("destroy() called");
    }

    @Override 
    public void service(ServletRequest request, ServletResponse response) 
        throws ServletException, IOException {
        System.out.println("service(req, res) called");
    }

    @Override
    public ServletConfig getServletConfig() {
        System.out.println("getServletConfig() called");
        return this.config;
    }

    @Override
    public String getServletInfo() {
        System.out.println("getServletInfo() called");
        return "version=1.0;author=yjchoi";
    }
}
