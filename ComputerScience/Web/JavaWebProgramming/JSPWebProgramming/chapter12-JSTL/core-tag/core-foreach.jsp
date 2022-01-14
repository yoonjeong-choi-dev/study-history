<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<%-- core 태그 임포트 --%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ page import="java.util.HashMap" %>

<%
    HashMap<String, Object> map = new HashMap<String, Object>();
    map.put("name", "YJ");
    map.put("today", new java.util.Date());
%>
<c:set var="intArray" value="<%= new int[] {1,2,3,4,5,6,7,8,9,10} %>" />
<c:set var="map" value="<%= map %>" />

<html>
<head>
    <title>forEach 반복문 처리</title>
<head>
<body>

<h4>1~10 사이 홀수 출력</h4>
<c:forEach var="i" begin="1" end="10" step="2">
${i} <br>
</c:forEach> <hr>

<h4>1부터 100까지 홀수의 합 </h4>
<c:set var="sum" value="0"/>
<c:forEach var="i" begin="1" end="100" step="2">
<c:set var="sum" value="${sum+i}"/>
</c:forEach>
Sum : ${sum}
<br><hr>

<h4>배열의 인덱스와 값 접근</h4>
<c:forEach var="item" items="${intArray}" varStatus="i">
${i.index}-th index : ${item} <br>
</c:forEach>
<hr>

<h4> Map 컬렉션 순회 </h4>
<c:forEach var="i" items="${map}" varStatus="s">
${i.key} = ${i.value} <br>
varStatus.count = ${s.count} <br>
varStatus.first = ${s.first} <br>
varStatus.last = ${s.last} <br>
varStatus.current = ${s.current} <br><br>
</c:forEach>

</body>
</html>