<%@ page contentType="text/html; charset=UTF-8" %>
<%@ page trimDirectiveWhitespaces="true" %>


<html>
<head>
    <title>비밀번호 변경</title>
<head>
<body>
<h1>${authUser.name}님, 비밀번호 변경을 완료했습니다</h1>
<a href="<%= request.getContextPath() %>">[메인페이지로 돌아가기]</a>
</body>
</html>