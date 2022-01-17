<%@ page contentType="text/html; charset=UTF-8" %>
<%@ page trimDirectiveWhitespaces="true" %>


<html>
<head>
    <title>회원가입 완료</title>
<head>
<body>
<h1>${param.name}님, 회원 가입에 성공했습니다</h1>
<a href="<%= request.getContextPath() %>">[메인페이지로 돌아가기]</a>
</body>
</html>