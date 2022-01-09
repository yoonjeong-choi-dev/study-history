<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<html>
<head>
    <title>Web App Path</title>
<head>
<body>
<h1>웹 어플리케이션 컨텍스트 경로 </h1>
request.getContextPath() : "<%= request.getContextPath() %>"
</body>
</html>