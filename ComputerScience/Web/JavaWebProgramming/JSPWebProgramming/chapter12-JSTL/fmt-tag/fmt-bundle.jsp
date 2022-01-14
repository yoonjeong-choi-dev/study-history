<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<%-- core 및 국제화 태그 임포트 --%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt" %>

<%-- 쿼리 파라미터를 이용하여 국제화 코드 출력 --%>
<c:if test="${param.lang == 'en'}">
<fmt:setLocale value="en" />
</c:if>

<%-- 번들 로드 --%>
<fmt:bundle basename="resource.message">

<%-- 번들의 메시지를 변수에 할당 --%>
<fmt:message key="TITLE" var="title"/>

<html>
<head>
    <title>국제화 태그 예제 1 : bundle</title>
<head>
<body>

<h3>Title : ${title} </h3>
<fmt:message key="GREETING"/><br>

<c:if test="${! empty param.id}"/>
<fmt:message key="VISITOR">
    <fmt:param value="${param.id}"/>
</fmt:message> <br>

</body>
</html>
</fmt:bundle>