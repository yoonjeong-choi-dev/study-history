<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<html>
<head>
    <title>include 디렉티브</title>
<head>
<body>

<% int number = 10; %>
<%-- 이후 includee.jsp 에서 선언한 변수들 접근 가능--%>
<%@ include file="/includes/includee.jsp" %>
<br><br>
includee.jsp 변수 접근 : <%= fromIncludee %>
</body>
</html>