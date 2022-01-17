<%@ page contentType="text/html; charset=UTF-8" %>
<%@ page trimDirectiveWhitespaces="true" %>

<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>


<html>
<head>
    <title>회원가입</title>
<head>
<body>
<h1>회원 가입 신청서</h1>
<form action="join.do" method="POST">
<p>
    아이디: </br> <input type="text" name="id" value="${param.id}">
    <c:if test="${errors.id}">ID를 입력하세요</c:if>
    <c:if test="${errors.duplicatedId}">중복된 ID입니다</c:if>
</p>
<p>
    이름: </br> <input type="text" name="name" value="${param.name}">
    <c:if test="${errors.name}">이름을 입력하세요</c:if>
</p>
<p>
    비밀번호 : </br> <input type="password" name="password" value="${param.password}">
    <c:if test="${errors.password}">비밀번호를 입력하세요</c:if>
</p>
<p>
    비밀번호 확인: </br> <input type="password" name="confirmPassword" value="${param.confirmPassword}">
    <c:if test="${errors.confirmPassword}">비밀번호 확인을 입력하세요</c:if>
    <c:if test="${errors.notMatch}">비밀번호가 일치하지 않습니다</c:if>
</p>
<input type="submit" value="가입">
</form>

</body>
</html>