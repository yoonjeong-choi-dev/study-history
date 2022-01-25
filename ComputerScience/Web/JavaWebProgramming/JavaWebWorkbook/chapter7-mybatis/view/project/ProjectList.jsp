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
    <th>
    <c:choose>
        <c:when test="${orderCond == 'id_asc'}">
            <a href="list.do?orderCond=id_desc">번호↑</a>
        </c:when>
        <c:when test="${orderCond == 'id_desc'}">
            <a href="list.do?orderCond=id_asc">번호↓</a>
        </c:when>
        <c:otherwise>
            <a href="list.do?orderCond=id_asc">번호︎</a>
        </c:otherwise>
    </c:choose>
    </th>

    <th>
    <c:choose>
        <c:when test="${orderCond == 'title_asc'}">
            <a href="list.do?orderCond=title_desc">제목↑</a>
        </c:when>
        <c:when test="${orderCond == 'title_desc'}">
            <a href="list.do?orderCond=title_asc">제목↓</a>
        </c:when>
        <c:otherwise>
            <a href="list.do?orderCond=title_asc">제목︎</a>
        </c:otherwise>
    </c:choose>
    </th>

    <th>
        <c:choose>
        <c:when test="${orderCond == 'start_date_asc'}">
            <a href="list.do?orderCond=start_date_desc">시작일↑</a>
        </c:when>
        <c:when test="${orderCond == 'start_date_desc'}">
            <a href="list.do?orderCond=start_date_asc">시작일↓</a>
        </c:when>
        <c:otherwise>
            <a href="list.do?orderCond=start_date_asc">시작일</a>
        </c:otherwise>
        </c:choose>
    </th>

    <th>
    <c:choose>
        <c:when test="${orderCond == 'end_date_asc'}">
            <a href="list.do?orderCond=ENDDATE_DESC">종료일↑</a>
        </c:when>
        <c:when test="${orderCond == 'end_date_desc'}">
            <a href="list.do?orderCond=end_date_asc">종료일↓</a>
        </c:when>
        <c:otherwise>
            <a href="list.do?orderCond=end_date_asc">종료일</a>
        </c:otherwise>
    </c:choose>
    </th>

    <th>
    <c:choose>
        <c:when test="${orderCond == 'state_asc'}">
            <a href="list.do?orderCond=state_desc">상태↑</a>
        </c:when>
        <c:when test="${orderCond == 'state_desc'}">
            <a href="list.do?orderCond=state_asc">상태↓</a>
        </c:when>
        <c:otherwise>
            <a href="list.do?orderCond=state_asc">상태</a>
        </c:otherwise>
    </c:choose>
    </th>

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