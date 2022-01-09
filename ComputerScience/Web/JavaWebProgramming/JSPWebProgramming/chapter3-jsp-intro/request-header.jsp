<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%-- <%@ page trimDirectiveWhitespaces="true" %> --%>

<%@ page import="java.util.Enumeration" %>
<html>
<head>
    <title>Request Header</title>
<head>
<body>
<%
    Enumeration headerEnum = request.getHeaderNames();
    while(headerEnum.hasMoreElements()) {
        String headerName = (String) headerEnum.nextElement();
        String headerValue = request.getHeader(headerName);
%>
<%= headerName %> = <%= headerValue %> <br>
<%
    }
%>

</body>
</html>