<%@ page language="java" contentType="text/html; charset=UTF-8" %>

<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>


<html>
<head>
    <title>프로젝트 목록</title>
<head>
<body>
<jsp:include page="/view/Header.jsp" />

<h1>프로젝트 목록</h1>
<p><a href='add.do'>프로젝트 생성</a></p>

<table border="1">
<tr>
    <th>번호</th>
    <th>제목</th>
    <th>시작일</th>
    <th>종료일</th>
    <th>상태</th>
    <th></th>
</tr>

<c:forEach var="project" items="${requestScope.projects}">
<tr>
<td>${project.id}</td>
<td><a href='update.do?id=${project.id}'>${project.title}</a></td>
<td>${project.startDate}</td>
<td>${project.endDate}</td>
<td>${project.state}</td>
<td><a href='delete.do?id=${project.id}'>[삭제]</a></td>
</tr>
</c:forEach>

</table>

<jsp:include page="/view/Tail.jsp" />
</body>
</html>