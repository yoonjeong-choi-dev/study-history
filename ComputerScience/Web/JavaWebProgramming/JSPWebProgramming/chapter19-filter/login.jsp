<%@ page contentType="text/html; charset=utf-8" %>
<%@ page trimDirectiveWhitespaces="true" %>

<%
	String memberId = request.getParameter("memberId");
	session.setAttribute("MEMBER", memberId);
%>
<html>
<head>
    <title>로그인 완료 </title>
</head>
<body>
<h1>로그인 완료 </h1>
</body>
</html>