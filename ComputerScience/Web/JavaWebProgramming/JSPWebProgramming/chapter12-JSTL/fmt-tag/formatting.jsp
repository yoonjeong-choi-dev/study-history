<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<%-- core 및 국제화 태그 임포트 --%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt" %>

<html>
<head>
    <title>포멧팅</title>
<head>
<body>

<h3>숫자 포멧팅</h3>
<c:set var="price" value="12345"/>
<fmt:formatNumber value="${price}" type="number" var="numberType"/>
숫자 : ${numberType}<br>
한국 통화 : 
    <fmt:formatNumber value="${price}" type="currency" currencySymbol="원"/>
    <br>
미국 통화 : 
    <fmt:formatNumber value="${price}" type="currency" currencyCode="USD" />
    <br>
퍼센트 : 
    <fmt:formatNumber value="${price}" type="percent" groupingUsed="false"/>
    <br>
패턴(0000000.00) : 
    <fmt:formatNumber value="${price}" pattern="0000000.00"/>
    <br>
<hr>

<h3>날짜 포멧팅</h3>
<c:set var="now" value="<%= new java.util.Date() %>"/>
full date : 
    <fmt:formatDate value="${now}" type="date" dateStyle="full"/>
    <br>
short date : 
    <fmt:formatDate value="${now}" type="date" dateStyle="short"/>
    <br>
default time : 
    <fmt:formatDate value="${now}" type="time"/>
    <br>
full time : 
    <fmt:formatDate value="${now}" type="time" timeStyle="full"/>
    <br>
short time : 
    <fmt:formatDate value="${now}" type="time" timeStyle="short"/>
    <br>
full date + time : 
    <fmt:formatDate value="${now}" type="both" dateStyle="full" timeStyle="full"/>
    <br>
custom date (z a h:mm) :
    <fmt:formatDate value="${now}" pattern="z a h:mm"/>
    <br>
<hr>

<h3> Time Zone </h3>
current time : 
    <fmt:formatDate value="${now}" type="both" dateStyle="full" timeStyle="full"/>
    <br>

<fmt:timeZone value="Hongkong">
hongkong time :
    <fmt:formatDate value="${now}" type="both" dateStyle="full" timeStyle="full"/>
    <br>
</fmt:timeZone>
<hr>

<h3> List of Timezones </h3>
<c:forEach var="id" items="<%= java.util.TimeZone.getAvailableIDs() %>">
    ${id} <br>
</c:forEach>

</body>
</html>
