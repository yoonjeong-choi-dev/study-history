<%@ tag pageEncoding="utf-8" %>
<%@ tag trimDirectiveWhitespaces="true"%>

<%-- 속성으로 받을 정적/동적 변수들 정의 --%>
<%@ attribute name="begin" required="true" type="java.lang.Integer" %>
<%@ attribute name="end" required="true" type="java.lang.Integer" %>

<%-- 태그 사용 페이지에서 전달한 접근 가능한 EL 변수 : 사용자에게 전달 받음--%>
<%@ attribute name="var" required="true" type="java.lang.String" rtexprvalue="false" %>
<%@ variable alias="sum" name-from-attribute="var" variable-class="java.lang.Integer" scope="NESTED" %>

<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>

<c:set var="sum" value="${0}"/>
<c:forEach var="num" begin="${begin}" end="${end}">
<c:set var="sum" value="${sum+num}"/>
</c:forEach>

<%-- 몸체 내용을 실행하기 전에 태그 파일에서 정의한 변수(sum)을 태그를 호출한 페이지에 전달 --%>
<jsp:doBody/>