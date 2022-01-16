package filter;

import java.io.IOException;
import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;


public class LoginCheckFilter implements Filter {
    @Override
    public void init(FilterConfig config) throws ServletException {}

    @Override
    public void doFilter(ServletRequest request, ServletResponse response,
        FilterChain chain) throws IOException, ServletException {
        
        HttpServletRequest httpReqeust = (HttpServletRequest) request;
        HttpSession session = httpReqeust.getSession(false);

        // 세션 정보가 있는 경우에만 로그인으로 판단
        boolean isLogin = false;
        if(session != null) {
            if (session.getAttribute("MEMBER") != null ) {
                isLogin = true;
            }
        }

        if (isLogin) {
            chain.doFilter(request, response);
        } else {
            // 로그인 하지 않은 경우 로그인 페이지로
            RequestDispatcher dispatcher = request.getRequestDispatcher("/loginForm.jsp");
            dispatcher.forward(request, response);
        }
    }

    @Override
    public void destroy() {}
}
