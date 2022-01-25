<%@ page language="java" contentType="text/html; charset=UTF-8" %>

<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>


<html>
<head>
    <title>회원 목록</title>
<head>
<body>
<jsp:include page="/view/Header.jsp" />

<h1>회원 목록</h1>
<p><a href='add.do'>회원 가입</a></p>

<table border="1">
<tr>
    <th>
    <c:choose>
        <c:when test="${orderCond == 'id_asc'}">
            <a href="list.do?orderCond=id_desc">번호↑</a>
        </c:when>
        <c:when test="${orderCond == 'id_desc'}">
            <a href="list.do?orderCond=id_asc">번호↑</a>
        </c:when>
        <c:otherwise>
            <a href="list.do?orderCond=id_asc">번호↑</a>
        </c:otherwise>
    </c:choose>
    </th>

    <th>
    <c:choose>
        <c:when test="${orderCond == 'name_asc'}">
            <a href="list.do?orderCond=name_desc">이름↑</a>
        </c:when>
        <c:when test="${orderCond == 'name_desc'}">
            <a href="list.do?orderCond=name_asc">이름↑</a>
        </c:when>
        <c:otherwise>
            <a href="list.do?orderCond=name_asc">이름</a>
        </c:otherwise>
    </c:choose>
    </th>

    <th>
    <c:choose>
        <c:when test="${orderCond == 'email_asc'}">
            <a href="list.do?orderCond=email_desc">이메일↑</a>
        </c:when>
        <c:when test="${orderCond == 'email_desc'}">
            <a href="list.do?orderCond=email_asc">이메일↑</a>
        </c:when>
        <c:otherwise>
            <a href="list.do?orderCond=email_asc">이메일</a>
        </c:otherwise>
    </c:choose>
    </th>

    <th>
    <c:choose>
        <c:when test="${orderCond == 'created_date_asc'}">
            <a href="list.do?orderCond=created_desc">가입일↑</a>
        </c:when>
        <c:when test="${orderCond == 'created_desc'}">
            <a href="list.do?orderCond=created_date_asc">가입일↑</a>
        </c:when>
        <c:otherwise>
            <a href="list.do?orderCond=created_date_asc">가입일</a>
        </c:otherwise>
    </c:choose>
    </th>

    <th></th>
</tr>

<c:forEach var="member" items="${requestScope.members}">
<tr>
<td>${member.id}</td>
<td><a href='update.do?id=${member.id}'>${member.name}</a></td>
<td>${member.email}</td>
<td>${member.createdDate}</td>
<td><a href='delete.do?id=${member.id}'>[삭제]</a></td>
</tr>
</c:forEach>


</table>
<jsp:include page="/view/Tail.jsp" />
</body>
</html>