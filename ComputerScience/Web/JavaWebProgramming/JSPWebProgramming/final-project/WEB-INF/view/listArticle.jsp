<%@ page contentType="text/html; charset=UTF-8" %>
<%@ page trimDirectiveWhitespaces="true" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>

<html>
<head>
    <title>게시글 목록</title>
<head>
<body>
<table border="1">
<tr>
    <td colspan="4"><a href="write.do">[게시글 작성]</a></td>
</tr>
<tr>
    <td>번호</td>
    <td>제목</td>
    <td>작성자</td>
    <td>조회수</td>
</tr>

<c:if test="${articlePage.hasNoArticles()}">
    <tr>
        <td colspan="4">등록된 게시글이 없습니다</td>
    </tr>
</c:if>

<c:forEach var="article" items="${articlePage.articleList}">
    <tr>
        <td>${article.number}</td>
        <td>
            <a href="read.do?no=${article.number}&pageNumber=${articlePage.currentPage}">
            <c:out value="${article.title}"/>
        </td>
        <td>${article.writer.name}</td>
        <td>${article.readCount}</td>
    </tr>
</c:forEach>

<c:if test="${articlePage.hasArticles()}">
    <tr>
        <td colspan="4">
            <c:if test="${articlePage.startPage > 5}">
                <a href="list.do?pageNumber=${articlePage.startPage - 5}">[이전]</a>
            </c:if>

            <c:forEach var="pageNumber" 
					   begin="${articlePage.startPage}" 
					   end="${articlePage.endPage}">
			<a href="list.do?pageNumber=${pageNumber}">[${pageNumber}]</a>
			</c:forEach>

			<c:if test="${articlePage.endPage < articlePage.totalPages}">
			<a href="list.do?pageNumber=${articlePage.startPage + 5}">[다음]</a>
			</c:if>
        </td>
    </tr>
    
    <%-- startPage: ${articlePage.startPage}<br>
    endPage: ${articlePage.endPage}<br>
    totalCount : ${articlePage.totalCount}<br>
    totalPages : ${articlePage.totalPages}<br>
    currentPage : ${articlePage.currentPage}<br> --%>
    
</c:if>

</table>
</body>
</html>