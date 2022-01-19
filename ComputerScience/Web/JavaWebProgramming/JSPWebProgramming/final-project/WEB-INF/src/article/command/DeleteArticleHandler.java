package article.command;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import article.service.ArticleNotFoundException;
import article.service.PermissionDeniedException;
import article.service.DeleteArticleService;
import auth.service.User;
import mvc.command.CommandHandler;

public class DeleteArticleHandler implements CommandHandler {
    private DeleteArticleService deleteService = new DeleteArticleService();

    @Override
    public String process(HttpServletRequest req, HttpServletResponse res) 
        throws Exception {
        try {
            User authUser = (User) req.getSession().getAttribute("authUser");

            String noVal = req.getParameter("no");
            int article_id = Integer.parseInt(noVal);

            deleteService.delete(authUser.getId(), article_id);

            return "/WEB-INF/view/deleteSuccess.jsp";
        } catch (ArticleNotFoundException e) {
            res.sendError(HttpServletResponse.SC_NOT_FOUND);
            return null;
        } catch (PermissionDeniedException e) {
            res.sendError(HttpServletResponse.SC_FORBIDDEN);
            return null;
        }
    } 
}
