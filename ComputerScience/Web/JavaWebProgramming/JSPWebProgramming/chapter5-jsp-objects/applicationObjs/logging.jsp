<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>
<%-- page 디렉티브 : 패키지 import --%>
<%@ page import="java.util.Calendar" %>
<html>
<head>
    <title>Logging</title>
<head>
<body>

<%
    Calendar cal = Calendar.getInstance();
    log("Log Message with JSP log function");
    application.log("Log Message with application log method");

    String curDate = String.format("%d-%d-%d", cal.get(Calendar.YEAR), cal.get(Calendar.MONTH)+1, cal.get(Calendar.DATE));
%>
<h1>
Check [Tomcat Dir]/logs/localhost.<%=curDate%>.log file!
</h1>
</body>
</html>