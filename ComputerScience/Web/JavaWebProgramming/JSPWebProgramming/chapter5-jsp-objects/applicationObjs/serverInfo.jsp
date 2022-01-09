<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>

<html>
<head>
    <title>Server Info</title>
<head>
<body>

서버 정보 : <%= application.getServerInfo() %> <br>
서블릿 규약 메이저 버전 : <%= application.getMajorVersion() %> <br>
서블릿 규약 마이너 버전 : <%= application.getMinorVersion() %> <br>
서블릿 규약 버전 : <%= application.getMajorVersion() %>.<%= application.getMinorVersion() %> <br>
</body>
</html>