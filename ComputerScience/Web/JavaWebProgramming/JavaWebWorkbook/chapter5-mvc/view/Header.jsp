<%@ page language="java" contentType="text/html; charset=UTF-8" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>



<div style="background-color:#00008b; color:#ffffff; height:20px; padding:5px;">
SPMS(Simple Project Management System)

<c:if test="${not empty sessionScope.member}">
<span style="float: right;">
    <strong>${sessionScope.member.name}</strong> 
    <a style="color:white; margin-left:5px;" href="${pageContext.request.contextPath}/auth/logout">로그아웃</a>
</span>
</c:if>

<c:if test="${empty sessionScope.member}">
    <span style="float: right;">
    <a style="color:white; margin-left:5px;" href="${pageContext.request.contextPath}/auth/login">로그인</a>
    </span>
</c:if>

</div>