package filter;

import java.io.IOException;

import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

public class LoginCheckFilter implements Filter {
    @Override
    public void doFilter(ServletRequest req, ServletResponse res, FilterChain chain)
    throws IOException, ServletException {
        HttpServletRequest request = (HttpServletRequest) req;
        HttpSession session = request.getSession();

        // 세션에 로그인 정보가 있는지 확인
        if(session == null || session.getAttribute("authUser") == null ) {
            // 로그인하지 않은 경우, 로그인 페이지로 리다이렉트
            HttpServletResponse response = (HttpServletResponse) res;
            response.sendRedirect(request.getContextPath()+"/login.do");
        } else {
            chain.doFilter(req, res);
        }
    }

    @Override
	public void init(FilterConfig config) throws ServletException {
	}

	@Override
	public void destroy() {
	}
}
