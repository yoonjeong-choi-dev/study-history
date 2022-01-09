<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%@ page trimDirectiveWhitespaces="true" %>

<%@ page import="java.util.Enumeration" %>
<html>
<head>
    <title></title>
<head>
<body>
<h1>application 속성 </h1>
<%
    Enumeration<String> attrEnum = application.getAttributeNames();
    while(attrEnum.hasMoreElements()) {
        String name = attrEnum.nextElement();
        Object value = application.getAttribute(name);
%>

<b> <%= name %> </b> : <%= value %> <br>
<%
    }
%>    
</body>
</html>