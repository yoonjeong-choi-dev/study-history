<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<%-- core 태그 임포트 --%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>

<%@ page import="member.MemberInfo" %>
<% MemberInfo member = new MemberInfo(); %>
<html>
<head>
    <title>Set/Remove 예제</title>
<head>
<body>

<h3>c:set 예제</h3>    
<c:set var="name" value="최윤정"/>
<c:set target="<%= member %>" property="name" value="Yoonjeong"/>
<c:set target="<%= member %>" property="email" value="yjchoi7166@gmail.com"/>
<c:set var="m" value="<%= member %>"/>
name 변수 : ${name} <br>
member.name : ${m.name} <br>
member.email : ${m.email} <br>
<hr>

<h3>c:remove 예제</h3>
<c:set var="name1" value="YJ-Page" scope="page"/>
<c:set var="name1" value="YJ-Request" scope="request"/>

page의 name1 : ${pageScope.name1}<br>
request의 name1 : ${requestScope.name1}<br>

<br> &lt;c:remove var="name1" scope="page"/&gt; 호출<br>
<c:remove var="name1" scope="page"/>

page의 name1 : ${pageScope.name1}<br>
request의 name1 : ${requestScope.name1}<br>
<hr>

</body>
</html>