package article.command;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import article.service.ArticlePage;
import article.service.ListAritcleService;

import mvc.command.CommandHandler;

public class ListArticleHandler implements CommandHandler {
    private ListAritcleService listService = new ListAritcleService();

    @Override
    public String process(HttpServletRequest req, HttpServletResponse res) 
    throws Exception{
        String pageNumberStr = req.getParameter("pageNumber");
        int pageNum = 1;
        if (pageNumberStr != null) {
            pageNum = Integer.parseInt(pageNumberStr);
        }

        ArticlePage articlePage = listService.getArticlePage(pageNum);
        req.setAttribute("articlePage", articlePage);
        return "/WEB-INF/view/listArticle.jsp";
        
    }
}
