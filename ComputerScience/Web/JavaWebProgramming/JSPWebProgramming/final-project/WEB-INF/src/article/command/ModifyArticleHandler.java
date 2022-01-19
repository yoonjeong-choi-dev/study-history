package article.command;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import article.model.ArticleData;
import article.service.ArticleNotFoundException;
import article.service.ModifyArticleService;
import article.service.ModifyRequest;
import article.service.PermissionDeniedException;
import article.service.ReadArticleService;
import auth.service.User;
import mvc.command.CommandHandler;

public class ModifyArticleHandler implements CommandHandler {
    private static final String FORM_VIEW = "/WEB-INF/view/modifyForm.jsp";

    private ReadArticleService readService = new ReadArticleService();
    private ModifyArticleService modifyService = new ModifyArticleService();

    @Override
    public String process(HttpServletRequest req, HttpServletResponse res)
            throws Exception {
        if (req.getMethod().equalsIgnoreCase("GET")) {
            return processForm(req, res);
        } else if (req.getMethod().equalsIgnoreCase("POST")) {
            return processSubmit(req, res);
        } else {
            res.setStatus(HttpServletResponse.SC_METHOD_NOT_ALLOWED);
            return null;
        }
    }

    private String processForm(HttpServletRequest req, HttpServletResponse res)
            throws IOException {
        try {
            User authUser = (User) req.getSession().getAttribute("authUser");

            String noVal = req.getParameter("no");
            int article_id = Integer.parseInt(noVal);
            ArticleData articleData = readService.getArticle(article_id, false);

            if (!canModify(authUser, articleData)) {
                res.sendError(HttpServletResponse.SC_FORBIDDEN);
                return null;
            }

            // 수정 폼에 수정할 데이터를 출력해야 한다
            ModifyRequest modifyRequest = new ModifyRequest(
                    authUser.getId(),
                    article_id,
                    articleData.getArticle().getTitle(),
                    articleData.getContent());

            req.setAttribute("modifyReq", modifyRequest);
            return FORM_VIEW;
        } catch (ArticleNotFoundException e) {
            res.sendError(HttpServletResponse.SC_NOT_FOUND);
            return null;
        }
    }

    // 수정 권한이 있는지 확인
    private boolean canModify(User authUser, ArticleData articleData) {
        String writerId = articleData.getArticle().getWriter().getId();
        return authUser.getId().equals(writerId);
    }

    private String processSubmit(HttpServletRequest req, HttpServletResponse res)
            throws Exception {
        User authUser = (User) req.getSession().getAttribute("authUser");
        
        String noVal = req.getParameter("no");
        int article_id = Integer.parseInt(noVal);

        ModifyRequest modifyReqeust = new ModifyRequest(
                authUser.getId(),
                article_id,
                req.getParameter("title"),
                req.getParameter("content"));
        req.setAttribute("modifyReq", modifyReqeust);

        Map<String, Boolean> errors = new HashMap<>();
        req.setAttribute("errors", errors);
        modifyReqeust.validate(errors);
        if (!errors.isEmpty()) {
            return FORM_VIEW;
        }
        try {
            modifyService.modify(modifyReqeust);
            return "/WEB-INF/view/modifySuccess.jsp";
        } catch (ArticleNotFoundException e) {
            res.sendError(HttpServletResponse.SC_NOT_FOUND);
            return null;
        } catch (PermissionDeniedException e) {
            res.sendError(HttpServletResponse.SC_FORBIDDEN);
            return null;
        }
    }
}
