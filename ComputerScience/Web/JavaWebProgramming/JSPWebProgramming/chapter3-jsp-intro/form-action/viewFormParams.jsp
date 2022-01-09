<%-- page 디렉티브 : 문서 타입, 인코딩 지정 --%>
<%@ page contentType="text/html; charset=UTF-8" %>
<%-- page 디렉티브 : 디렉티브나 스크립트 코드로 인한 공백 제거 --%>
<%-- <%@ page trimDirectiveWhitespaces="true" %> --%>

<%@ page import="java.util.Enumeration" %>
<%@ page import="java.util.Map" %>
<%
    request.setCharacterEncoding("utf-8");
%>
<html>
<head>
    <title>Form Params</title>
<head>
<body>

<b>request.getParameter()</b><br>
name 파라미터 = <%= request.getParameter("name")%> <br>
address 파라미터 = <%= request.getParameter("address")%> <br>

<p>
<b>request.getParameterValues()</b><br>
<%
    String[] values = request.getParameterValues("pet");

    // 체크박스로 전송되는 pet 파라미터는 아무것도 전송이 안될 수 있음
    if (values != null) {
    for (int i = 0 ; i < values.length ; i++) {
%>
    <%= values[i] %>
<%
        }
    }
%>

<p>
<b>request.getParameterNames()</b><br>
<%
    Enumeration paramEnum = request.getParameterNames();
    while(paramEnum.hasMoreElements()) {
        String name= (String)paramEnum.nextElement();
%>
    <%= name %>
<%
    }
%>

<p>
<b>request.getParameterMap()</b><br>
<%
    Map paramMap = request.getParameterMap();
    String[] nameParams = (String[])paramMap.get("name");
    if (nameParams != null) {
%>
    name = <%= nameParams[0] %>
<%
    }
%>

</body>
</html>