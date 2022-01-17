<%@ page contentType="text/html; charset=UTF-8" %>
<%@ page trimDirectiveWhitespaces="true" %>

<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>


<html>
<head>
    <title>로그인</title>
<head>
<body>
<h1>로그인</h1>
<form action="login.do" method="POST">
<c:if test="${errors.idOrPwNotMath}">
<h3 style="color: red;">아이디와 암호가 일치하지 않습니다</h3>
</c:if>
<p>
    아이디: </br> <input type="text" name="id" value="${param.id}">
    <c:if test="${errors.id}">ID를 입력하세요</c:if>
</p>
<p>
    비밀번호 : </br> <input type="password" name="password" value="${param.password}">
    <c:if test="${errors.password}">비밀번호를 입력하세요</c:if>
</p>
<input type="submit" value="로그인">
</form>

</body>
</html>