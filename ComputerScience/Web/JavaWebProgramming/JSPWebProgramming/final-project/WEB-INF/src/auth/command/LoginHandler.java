package auth.command;

import java.util.HashMap;
import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import auth.service.LoginFailException;
import auth.service.LoginService;
import auth.service.User;
import mvc.command.CommandHandler;

public class LoginHandler implements CommandHandler {

    private static final String FORM_VIEW = "/WEB-INF/view/loginForm.jsp";
    private LoginService loginService = new LoginService();

    @Override
    public String process(HttpServletRequest req, HttpServletResponse res)
            throws Exception {
        // GET : 로그인 폼, POST : 로그인 후 메인 페이지
        if (req.getMethod().equalsIgnoreCase("GET")) {
            return processForm(req, res);
        } else if (req.getMethod().equalsIgnoreCase("POST")) {
            return processSubmit(req, res);
        } else {
            res.setStatus(HttpServletResponse.SC_METHOD_NOT_ALLOWED);
            return null;
        }
    }

    private String processForm(HttpServletRequest req, HttpServletResponse res) {
        return FORM_VIEW;
    }

    private String processSubmit(HttpServletRequest req, HttpServletResponse res)
            throws Exception {
        String id = trim(req.getParameter("id"));
        String password = req.getParameter("password");

        Map<String, Boolean> errors = new HashMap<>();
        req.setAttribute("errors", errors);

        if (id == null || id.isEmpty()) {
            errors.put("id", Boolean.TRUE);
        }

        if (password == null || password.isEmpty()) {
            errors.put("password", Boolean.TRUE);
        }

        // 유효하지 않은 요청 데이터 : 로그인 폼으로
        if (!errors.isEmpty()) {
            return FORM_VIEW;
        }

        // 로그인 처리
        try {
            // 로그인 성공 시, 세션에 저장
            User user = loginService.login(id, password);
            req.getSession().setAttribute("authUser", user);
            
            // 메인 페이지로 리다이렉트
            res.sendRedirect(req.getContextPath()+"/index.jsp");
            return null;
        } catch (LoginFailException ex) {
            errors.put("idOrPwNotMath", Boolean.TRUE);
            return FORM_VIEW;
        }
    }

    private String trim(String str) {
        return str == null ? null : str.trim();
    }
}
