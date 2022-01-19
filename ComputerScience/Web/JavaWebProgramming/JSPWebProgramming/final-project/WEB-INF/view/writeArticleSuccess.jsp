<%@ page contentType="text/html; charset=UTF-8" %>
<%@ page trimDirectiveWhitespaces="true" %>


<html>
<head>
    <title>게시글 작성 완료</title>
<head>
<body>
<h1>${authUser.name}님, 게시글을 등록했습니다</h1>
${ctxPath = pageContext.request.contextPath; ''}
<a href="${ctxPath}/article/list.do">[게시글목록보기]</a>
<a href="${ctxPath}/article/read.do?no=${newArticleNo}">[게시글내용보기]</a>
<br><br>
<a href="${ctxPath}">[메인페이지로 돌아가기]</a>
</body>
</html>