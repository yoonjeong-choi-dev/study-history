package member.command;

import java.util.HashMap;
import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import member.service.DuplicateIdException;
import member.service.JoinRequest;
import member.service.JoinService;
import mvc.command.CommandHandler;

public class JoinHandler implements CommandHandler {
    private static final String FORM_VIEW = "/WEB-INF/view/joinForm.jsp";
    private JoinService joinService = new JoinService();

    @Override
    public String process(HttpServletRequest req, HttpServletResponse res) {
        // GET : 회원 가입 폼, POST : 회원 가입 처리 및 결과 페이지
        if( req.getMethod().equalsIgnoreCase("GET")) {
            return processForm(req, res);
        } else if(req.getMethod().equalsIgnoreCase("POST")) {
            return processSubmit(req, res);
        } else {
            res.setStatus(HttpServletResponse.SC_METHOD_NOT_ALLOWED);
            return null;
        }
    }

    private String processForm(HttpServletRequest req, HttpServletResponse res) {
        return FORM_VIEW;
    }

    private String processSubmit(HttpServletRequest req, HttpServletResponse res) {
        JoinRequest joinReq = new JoinRequest();
        joinReq.setId(req.getParameter("id"));
        joinReq.setName(req.getParameter("name"));
        joinReq.setPassword(req.getParameter("password"));
        joinReq.setConfirmPassword(req.getParameter("confirmPassword"));

        Map<String, Boolean> errors = new HashMap<>();
        req.setAttribute("errors", errors);

        joinReq.validate(errors);

        // 유효하지 않은 요청 데이터 : 회원가입 폼으로 
        if(!errors.isEmpty()) {
            return FORM_VIEW;
        }

        // 회원 가입 처리
        try {
            joinService.join(joinReq);
            return "/WEB-INF/view/joinSuccess.jsp";
        } catch (DuplicateIdException ex) {
            errors.put("duplicatedId", Boolean.TRUE);
            return FORM_VIEW;
        }
    }
}
