package article.service;

import java.util.List;

import article.model.Article;

public class ArticlePage {
    private int totalCount;
    private int currentPage;
    private List<Article> articleList;
    private int totalPages;
    private int startPage;
    private int endPage;

    public ArticlePage(int totalCount, int currentPage, 
        int size, List<Article> articleList) {

        this.totalCount = totalCount;
        this.currentPage = currentPage;
        this.articleList = articleList;
        
        if (totalCount == 0) {
            totalPages = 0;
            startPage = 0;
            endPage = 0;
        } else {
            totalPages = totalCount / size;
            if( totalPages % size > 0) {
                totalPages++;
            }

            int remainders = currentPage % 5;
            startPage = currentPage / 5 * 5 +1;
            if (remainders == 0) startPage -= 5;

            endPage = startPage + 4;
            if (endPage > totalPages) endPage = totalPages;
        }
    }

    public int getTotalCount() {
        return totalCount;
    }

    public boolean hasNoArticles() {
        return totalCount == 0;
    }

    public boolean hasArticles() {
        return totalCount > 0;
    }

    public int getCurrentPage() {
        return currentPage;
    }

    public int getTotalPages() {
        return totalPages;
    }

    public List<Article> getArticleList() {
        return articleList;
    }

    public int getStartPage() {
        return startPage;
    }
    
    public int getEndPage() {
        return endPage;
    }
}
