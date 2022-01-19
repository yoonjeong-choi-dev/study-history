package article.command;

import java.util.HashMap;
import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import article.model.Writer;
import article.service.WriteArticleService;
import article.service.WriteRequest;
import auth.service.User;
import mvc.command.CommandHandler;

public class WriteArticleHandler implements CommandHandler {
    private static final String FORM_VIEW = "/WEB-INF/view/writeArticleForm.jsp";
    private WriteArticleService writeService = new WriteArticleService();

    @Override
    public String process(HttpServletRequest req, HttpServletResponse res) {
        // GET : 게시글 작성 폼, POST : 게시글 등록 처리 및 결과 페이지
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

    private String processSubmit(HttpServletRequest req, HttpServletResponse res) {
        // 사용자 정보 구하기
        User user = (User) req.getSession().getAttribute("authUser");

        Map<String, Boolean> errors = new HashMap<>();
        req.setAttribute("errors", errors);

        // 요청 데이터 변환
        WriteRequest writeReq = createRequest(user, req);
        writeReq.validate(errors);

        // 유효하지 않은 요청 데이터 : 게시글 작성 폼으로
        if (!errors.isEmpty()) {
            return FORM_VIEW;
        }

        // 게시글 저장 처리
        int newArticleNo = writeService.write(writeReq);
        req.setAttribute("newArticleNo", newArticleNo);
        return "/WEB-INF/view/writeArticleSuccess.jsp";
    }

    private WriteRequest createRequest(User user, HttpServletRequest req) {
        return new WriteRequest(
            new Writer(user.getId(), user.getName()), 
            req.getParameter("title"), 
            req.getParameter("content"));
    }
}
