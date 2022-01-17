<%@ page contentType="text/html; charset=UTF-8" %>
<%@ page trimDirectiveWhitespaces="true" %>
<%@ taglib prefix="u" tagdir="/WEB-INF/tags" %>


<html>
<head>
    <title>게시판 프로젝트</title>
<head>
<body>
<h1>게시판 프로젝트</h1>
<u:isLogin>
	<strong>${authUser.name}</strong>님, 안녕하세요.<br>
	<a href="logout.do">[로그아웃하기]</a><br>
	<a href="changePw.do">[암호변경하기]</a>
</u:isLogin>
<u:notLogin>
	<a href="join.do">[회원가입하기]</a><br>
	<a href="login.do">[로그인하기]</a>
</u:notLogin>
</body>
</html>