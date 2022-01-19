<%@ page contentType="text/html; charset=UTF-8" %>
<%@ page trimDirectiveWhitespaces="true" %>

<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>


<html>
<head>
    <title>게시글 수정</title>
<head>
<body>
<h1>게시글 수정하기</h1>
<form action="modify.do" method="POST">
<input type="hidden" name="no" value="${modifyReq.articleNumber}">
<p>
    번호: </br> ${modifyReq.articleNumber}
</p>
<p>
    제목: </br> <input type="text" name="title" value="${modifyReq.title}">
    <c:if test="${errors.title}">제목을 입력하세요</c:if>
</p>
<p>
    내용 : </br> 
    <textarea name="content" rows="5" cols="30">${modifyReq.content}</textarea>
</p>
<input type="submit" value="수정하기">
</form>

</body>
</html>