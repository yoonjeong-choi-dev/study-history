<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<html>
<head>
    <title>from.jsp</title>
<head>
<body>
    <h1>from.jsp에서 생성한 페이지</h1>
    <jsp:forward page="../to/to.jsp"/>
</body>
</html>