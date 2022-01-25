<%@ page language="java" contentType="text/html; charset=UTF-8" %>


<html>
<head>
    <title>로그인</title>
<head>
<body>

<h1>사용자 로그인</h1>
<form action="login.do" method="POST">
이메일 : <input type="text" name="email"><br>
비밀번호 : <input type="password" name="password"><br>
<input type="submit" value="로그인">
</form>

<jsp:include page="/view/Tail.jsp" />
</body>
</html>