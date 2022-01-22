<%@ page language="java" contentType="text/html; charset=UTF-8" %>

<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>


<html>
<head>
    <title>회원 목록</title>
<head>
<body>
<jsp:include page="/view/Header.jsp" />

<h1>회원 목록</h1>
<p><a href='add'>회원 가입</a></p>

<c:forEach var="member" items="${requestScope.members}">
${member.id},
<a href='update?id=${member.id}'>${member.name}</a>
${member.email},
${member.createdDate}
<a href='delete?id=${member.id}'>[삭제]</a>
<hr>
</c:forEach>


<jsp:include page="/view/Tail.jsp" />
</body>
</html>