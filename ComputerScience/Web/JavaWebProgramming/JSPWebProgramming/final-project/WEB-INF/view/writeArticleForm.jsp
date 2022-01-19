<%@ page contentType="text/html; charset=UTF-8" %>
<%@ page trimDirectiveWhitespaces="true" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>

<html>
<head>
    <title>게시글 등록</title>
<head>
<body>
<h1>게시글 등록</h1>
<form action="write.do" method="POST">
<p>
    제목 : </br> <input type="text" name="title" value="${param.title}">
    <c:if test="${errors.title}">제목을 입력하세요</c:if>
</p>
<p>
    내용 : </br> 
    <textarea name="content" rows="5" cols="30">
        ${param.content}
    </textarea>
</p>
<input type="submit" value="게시글 등록">
</form>
</body>
</html>