package member.command;

import java.util.HashMap;
import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import auth.service.User;
import member.service.ChangePasswordService;
import member.service.InvalidPasswordException;
import member.service.MemberNotFoundException;
import mvc.command.CommandHandler;

public class ChangePasswordHandler implements CommandHandler {
    private static final String FORM_VIEW = "/WEB-INF/view/changePwForm.jsp";
    private ChangePasswordService changePwService = new ChangePasswordService();

    @Override
    public String process(HttpServletRequest req, HttpServletResponse res)
            throws Exception {
        // GET : 회원 가입 폼, POST : 회원 가입 처리 및 결과 페이지
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
        // 사용자 정보 구하기
        User user = (User) req.getSession().getAttribute("authUser");

        Map<String, Boolean> errors = new HashMap<>();
        req.setAttribute("errors", errors);

        String curPw = req.getParameter("curPw");
        String newPw = req.getParameter("newPw");

        if (curPw == null || curPw.isEmpty()) {
            errors.put("curPw", Boolean.TRUE);
        }

        if (newPw == null || newPw.isEmpty()) {
            errors.put("newPw", Boolean.TRUE);
        }

        // 유효하지 않은 요청 데이터 : 비밀번호 변경 폼으로
        if (!errors.isEmpty()) {
            return FORM_VIEW;
        }

        // 비밀번호 변경 처리
        try {
            changePwService.changePassword(user.getId(), curPw, newPw);
            return "/WEB-INF/view/changePwSuccess.jsp";
        } catch (InvalidPasswordException ex) {
            errors.put("wrongPw", Boolean.TRUE);
            return FORM_VIEW;
        } catch (MemberNotFoundException ex) {
            res.sendError(HttpServletResponse.SC_BAD_REQUEST);
            return null;
        }
    }
}
