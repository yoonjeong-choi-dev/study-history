<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%@ page import="java.util.Enumeration" %>

<html>
<head>
    <title>Read Web.xml</title>
<head>
<body>

초기화 파라미터 목록
<ul>
<%
    Enumeration<String> initParamEnum = application.getInitParameterNames();
    while(initParamEnum.hasMoreElements()) {
        String initParamName = initParamEnum.nextElement();
%>
<li>
    <%= initParamName %> = <%= application.getInitParameter(initParamName) %>
</li>
<%
    }
%>
</ul>
</body>
</html>