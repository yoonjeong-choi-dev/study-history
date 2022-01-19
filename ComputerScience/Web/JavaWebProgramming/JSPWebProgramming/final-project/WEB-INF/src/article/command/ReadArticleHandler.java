package article.command;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import article.service.ArticleNotFoundException;
import article.service.ArticleContentNotFoundException;
import article.model.ArticleData;
import article.service.ReadArticleService;

import mvc.command.CommandHandler;

public class ReadArticleHandler implements CommandHandler {

    private ReadArticleService readService = new ReadArticleService();

    @Override
    public String process(HttpServletRequest req, HttpServletResponse res)
            throws Exception {
        String noVal = req.getParameter("no");
        int article_id = Integer.parseInt(noVal);

        try {
            ArticleData articleData = readService.getArticle(article_id, true);
            req.setAttribute("articleData", articleData);
            return "/WEB-INF/view/readArticle.jsp";
        } catch (ArticleNotFoundException | ArticleContentNotFoundException ex) {
            req.getServletContext().log("no article", ex);
            res.sendError(HttpServletResponse.SC_NOT_FOUND);
            return null;
        }
    }
}
