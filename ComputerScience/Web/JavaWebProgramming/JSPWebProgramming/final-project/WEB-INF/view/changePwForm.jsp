<%@ page contentType="text/html; charset=UTF-8" %>
<%@ page trimDirectiveWhitespaces="true" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>

<html>
<head>
    <title>비밀번호 변경</title>
<head>
<body>
<h1>비밀번호 변경</h1>
<form action="changePw.do" method="POST">
<p>
    현재 비밀번호 : </br> <input type="password" name="curPw">
    <c:if test="${errors.curPw}">현재 비밀번호를 입력하세요</c:if>
    <c:if test="${errors.wrongPw}">현재 비밀번호가 일치하지 않습니다</c:if>
</p>
<p>
    비밀번호 : </br> <input type="password" name="newPw">
    <c:if test="${errors.newPw}">새 비밀번호를 입력하세요</c:if>
</p>
<input type="submit" value="가입">
</form>
</body>
</html>