<%@ page contentType="text/html; charset=utf-8" %>
<%@ page trimDirectiveWhitespaces="true" %>

<html>
<head>
    <title>로그인</title>
</head>
<body>
<form action="<%= request.getContextPath() %>/login.jsp" method="POST">
아이디<input type="text" name="memberId">
암호<input type="password" name="password">
<input type="submit" value="로그인">
</form>
</body>
</html>